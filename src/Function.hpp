//
// Created by Twometer on 14 Nov 2021.
//

#ifndef LIBNEKO_FUNCTION_HPP
#define LIBNEKO_FUNCTION_HPP

#include <assert.h>

//
// This is the Lambda implementation from https://www.codeproject.com/Articles/313312/Cplusplus11-Lambda-Storage-Without-libcplusplus
// which was released under the Code Project Open Source License.
//
// Modifications done
//   - Slight renaming and refactoring
//   - Fix missing `this->` to make it compile
//

namespace nk {

    template<typename T>
    class FunctionExecutor {
    };

    template<typename Out, typename... In>
    class FunctionExecutor<Out(In...)> {
    public:
        Out operator()(In... in) {
            assert(m_lambda != nullptr);
            return m_execute_function(m_lambda, in...);
        }

    protected:
        FunctionExecutor(void *&lambda) : m_lambda(lambda) {}

        ~FunctionExecutor() = default;

        template<typename T>
        void generate_executor(T const &lambda) {
            m_execute_function = [](void *lambda, In... arguments) -> Out {
                return ((T *) lambda)->operator()(arguments...);
            };
        }

        void receive_executor(FunctionExecutor<Out(In...)> const &other) {
            m_execute_function = other.m_execute_function;
        }

    private:
        void *&m_lambda;

        Out (*m_execute_function)(void *, In...);
    };

    template<typename... In>
    class FunctionExecutor<void(In...)> {
    public:
        void operator()(In... in) {
            assert(m_lambda != nullptr);
            m_execute_function(m_lambda, in...);
        }

    protected:
        FunctionExecutor(void *&lambda) : m_lambda(lambda) {}

        ~FunctionExecutor() = default;

        template<typename T>
        void generate_executor(T const &lambda) {
            m_execute_function = [](void *lambda, In... arguments) {
                return ((T *) lambda)->operator()(arguments...);
            };
        }

        void receive_executor(FunctionExecutor<void(In...)> const &other) {
            m_execute_function = other.m_execute_function;
        }

    private:
        void *&m_lambda;

        void (*m_execute_function)(void *, In...);
    };

    template<typename T>
    class Function {
    };

    template<typename Out, typename... In>
    class Function<Out(In...)> : public FunctionExecutor<Out(In...)> {
    public:
        Function() : FunctionExecutor<Out(In...)>(m_lambda),
                     m_lambda(nullptr), m_delete_function(nullptr), m_copy_function(nullptr) {
        }

        Function(Function<Out(In...)> const &other) : FunctionExecutor<Out(In...)>(m_lambda),
                                                      m_lambda(other.m_copy_function ? other.m_copy_function(
                                                              other.m_lambda)
                                                                                     : nullptr),
                                                      m_delete_function(other.m_delete_function),
                                                      m_copy_function(other.m_copy_function) {
            this->receive_executor(other);
        }

        template<typename T>
        Function(T const &lambda) : FunctionExecutor<Out(In...)>(this->m_lambda), m_lambda(nullptr) {
            // Copy should set all variables
            copy(lambda);
        }

        ~Function() {
            if (m_delete_function != nullptr)
                m_delete_function(m_lambda);
        }

        Function<Out(In...)> &operator=(Function<Out(In...)> const &other) {
            this->m_lambda = other.m_copy_function ? other.m_copy_function(other.m_lambda) : nullptr;
            receive_executor(other);
            this->m_delete_function = other.m_delete_function;
            this->m_copy_function = other.m_copy_function;
            return *this;
        }

        template<typename T>
        Function<Out(In...)> &operator=(T const &lambda) {
            copy(lambda);
            return *this;
        }

        operator bool() {
            return m_lambda != nullptr;
        }

    private:
        template<typename T>
        void copy(T const &lambda) {
            if (this->m_lambda != nullptr)
                m_delete_function(this->m_lambda);
            this->m_lambda = new T(lambda);

            this->generate_executor(lambda);

            m_delete_function = [](void *lambda) {
                delete (T *) lambda;
            };

            m_copy_function = [](void *lambda) -> void * {
                return lambda ? new T(*(T *) lambda) : nullptr;
            };
        }

        void *m_lambda;

        void (*m_delete_function)(void *);

        void *(*m_copy_function)(void *);
    };

}

#endif //LIBNEKO_FUNCTION_HPP
