#ifndef SIZEOF_HPP
#define SIZEOF_HPP
template <typename T>
void test_sizeof() {
    T t{T{}};
    T *t_ptr{nullptr};
    P_FORMAT_BEGIN << " sizeof(T) = " << sizeof(t) << "\n";
    P_FORMAT_BEGIN << " sizeof t_ptr = " << sizeof(t_ptr) << "\n";
    P_FORMAT_BEGIN << " sizeof *t_ptr = " << sizeof(*t_ptr) << "\n";
    P_FORMAT_BEGIN << " sizeof &t_ptr = " << sizeof(&t_ptr) << "\n";
}
#endif