#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <iomanip>
#include "formatter.hpp"
#ifndef DEFAULT_INT_HPP
#define DEFAULT_INT_HPP
template <typename T>
struct SizeOfT_t
{
    static constexpr std::tuple<int, int> size =
        std::make_tuple(sizeof(T), std::numeric_limits<T>::digits);
};
template <typename T>
static constexpr auto size_v = SizeOfT_t<T>::size;
enum class IntDefaultE : std::int8_t
{
    INT_8 = 8,
    INT_16 = 16,
    INT_32 = 32,
    INT_64 = 64,
    UNDEFINED = 0
};
constexpr auto get_int_type()
{
    if constexpr (size_v<int> == size_v<int8_t>)
    {
        return IntDefaultE::INT_8;
    }
    else if (size_v<int> == size_v<int16_t>)
    {
        return IntDefaultE::INT_16;
    }
    else if (size_v<int> == size_v<int32_t>)
    {
        return IntDefaultE::INT_32;
    }
    else if (size_v<int> == size_v<int64_t>)
    {
        return IntDefaultE::INT_64;
    }
    else
    {
        return IntDefaultE::UNDEFINED;
    }
}
template <typename T, typename Enabler = void>
struct IntDefaultT : std::false_type
{
};
template <typename T>
struct IntDefaultT<T, typename std::enable_if_t<std::is_same_v<int, T>>>
    : std::true_type
{
    using default_int_t = T;
};
template <typename T>
using int_default_t = typename IntDefaultT<T>::default_int_t;
template <typename T>
static constexpr auto int_default_v = IntDefaultT<T>::value;
constexpr auto get_int_type_2()
{
    if constexpr (int_default_v<int8_t>)
    {
        return IntDefaultE::INT_8;
    }
    else if (int_default_v<int16_t>)
    {
        return IntDefaultE::INT_16;
    }
    else if (int_default_v<int32_t>)
    {
        return IntDefaultE::INT_32;
    }
    else if (int_default_v<int64_t>)
    {
        return IntDefaultE::INT_64;
    }
    else
    {
        return IntDefaultE::UNDEFINED;
    }
}
template <typename...>
struct is_one_of : std::false_type
{
};
template <typename... T>
static constexpr auto is_one_of_v = is_one_of<T...>::value;
template <typename F, typename S, typename... T>
struct is_one_of<F, S, T...>
{
    static constexpr bool value = std::is_same_v<F, S> || is_one_of_v<F, T...>;
    using type = F;
};
using default_int_t = is_one_of<int, int8_t, int64_t, int32_t, int16_t>;
using default_int = default_int_t::type;
static constexpr auto INT_SIZE = get_int_type();
static constexpr auto INT_SIZE_2 = get_int_type_2();

void test_1(int64_t v)
{
    (void)v;
    P_FORMAT_BEGIN << "int = [64]";
};
void test_1(int32_t v)
{
    (void)v;
    P_FORMAT_BEGIN << "int = [32]";
};
void test_1(int16_t v)
{
    (void)v;
    P_FORMAT_BEGIN << "int = [16]";
};
void test_1(int8_t v)
{
    (void)v;
    P_FORMAT_BEGIN << "int = [8]";
};
void test_1(int *v)
{
    (void)v;
    P_FORMAT_BEGIN << "int = [pointer]";
};
#endif
