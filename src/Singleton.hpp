//
// Created by Twometer on 15 Nov 2021.
//

#ifndef LIBNEKO_SINGLETON_HPP
#define LIBNEKO_SINGLETON_HPP

#define NK_MAKE_SINGLETON(class_name)           \
public:                                         \
  static class_name *get_instance() {           \
    static auto instance = new class_name();    \
    return instance;                            \
  }                                             \
private:

#endif //LIBNEKO_SINGLETON_HPP
