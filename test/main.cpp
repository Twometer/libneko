//
// Created by Twometer on 12 Nov 2021.
//

#include <String.hpp>
#include <StringBuffer.hpp>
#include <Path.hpp>
#include <cstdio>
#include <Hash.hpp>

void test_string() {
    nk::String str;
    assert(str.length() == 0);
    assert(str.is_empty());
    assert(str.trim().is_empty());

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

void test_string_split() {
    nk::String str("comma,separated,values");
    auto parts = str.split(',');
    assert(parts[0] == "comma");
    assert(parts[1] == "separated");
    assert(parts[2] == "values");
}

void test_vector_simple() {
    nk::Vector<int> vector;
    vector.push(69);
    vector.push(42);
}

nk::String test_create_string(int i) {
    return nk::String("test_") + i;
}

nk::Vector<nk::String> test_vector_return() {
    nk::Vector<nk::String> vector;
    vector.push("test_1");
    vector.push(test_create_string(2));
    return vector;
}

void test_vector_complex() {
    auto vec = test_vector_return();
    vec.push("test_3");
    assert(vec[0] == "test_1");
    assert(vec[1] == "test_2");
    assert(vec[2] == "test_3");
}

void test_vector_empty() {
    nk::Vector<nk::String> vec;
    assert(vec.is_empty());
    assert(vec.length() == 0);

    auto iterator_called = false;
    for (const auto &s : vec) {
        iterator_called = true;
    }

    assert(!iterator_called);
}

void test_string_buffer() {
    nk::StringBuffer buf;
    assert(buf.length() == 0);
    assert(buf.is_empty());

    buf.append('4');
    buf.append("20");
    buf.append(nk::String("69"));
    buf.append_newline();

    auto expect = nk::String("42069\n");
    assert(buf.length() == expect.length());
    assert(buf.to_string() == expect);
    assert(!buf.is_empty());
}

void test_paths() {
    nk::Path abs_path("/test/1/2/3/../test.f");
    const auto &parts = abs_path.parts();
    assert(parts[0] == "test");
    assert(parts[1] == "1");
    assert(parts[2] == "2");
    assert(parts[3] == "test.f");
    assert(abs_path.is_absolute() == true);
    assert(abs_path.name() == "test.f");
    assert(abs_path.is_root() == false);

    nk::Path root_path("/");
    assert(root_path.parts().is_empty());
    assert(root_path.name().is_empty());
    assert(root_path.is_root() == true);
    assert(root_path.is_absolute() == true);
    assert(root_path.to_string() == "/");

    nk::Path combined_path = nk::Path("path/1/subdir/") + nk::Path("../path/2");
    assert(combined_path.parts()[0] == "path");
    assert(combined_path.parts()[1] == "1");
    assert(combined_path.parts()[2] == "path");
    assert(combined_path.parts()[3] == "2");
    assert(!combined_path.is_absolute());
    assert(!combined_path.is_root());
}

nk::hash_t strhash(const char *c) {
    return nk::hash(c);
}

void test_hash() {
    assert(nk::hash(1234) == 1234);
    assert(nk::hash(12391293102873910823ull) == 12391293102873910823ull);
    assert(strhash("test") == 3556498);
}

int main() {
    test_string();
    test_string_split();
    test_vector_simple();
    test_vector_complex();
    test_vector_empty();
    test_string_buffer();
    test_paths();
    test_hash();
    return 0;
}
