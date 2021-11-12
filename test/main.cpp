//
// Created by Twometer on 12 Nov 2021.
//

#include <cstdio>

#include <String.hpp>

void test_string() {
    nk::String str;
    assert(str.length() == 0);
    assert(str.is_empty());

    str = "  test ";
    assert(str == "  test ");

    str = str.trim();
    assert(str == "test");

    assert(str.starts_with(""));
    assert(str.starts_with("te"));
    assert(str.starts_with("test"));
    assert(!str.starts_with("est"));
    assert(!str.starts_with("asdfgh"));
    assert(!str.starts_with("f"));

    assert(str.ends_with(""));
    assert(str.ends_with("st"));
    assert(str.ends_with("test"));
    assert(!str.ends_with("sest"));
    assert(!str.ends_with("asdfgh"));
    assert(!str.ends_with("af"));

    assert(str.contains("est"));
    assert(str.contains("es"));
    assert(str.contains("tes"));
    assert(!str.contains("ses"));

    assert(str.index_of("t") == 0);
    assert(str.index_of("st") == 2);

    assert(str.remove(str.index_of("st")) == "te");
    assert(str.substring(str.index_of("st")) == "st");

    assert(str + "123" == "test123");

    str += '1';
    assert(str == "test1");
}

void test_vector_simple() {
    nk::Vector<int> vector;
    vector.push(69);
    vector.push(42);
}

nk::Vector<nk::String> test_vector_return() {
    nk::Vector<nk::String> vector;
    vector.push("test1");
    vector.push("test2");
    return vector;
}

void test_vector_complex() {
    auto vec = test_vector_return();
    vec.push("test3");
    printf("%s\n", vec[0].c_str());
}

int main() {
    test_string();
    test_vector_simple();
    test_vector_complex();
    return 0;
}
