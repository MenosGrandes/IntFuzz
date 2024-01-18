#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int get_int_size_c()
{
    int c;
    return sizeof(c);
}

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
    std::cout << "64\n";
};
void test_1(int32_t v)
{
    (void)v;
    std::cout << "32\n";
};
void test_1(int16_t v)
{
    (void)v;
    std::cout << "16\n";
};
void test_1(int8_t v)
{
    (void)v;
    std::cout << "8\n";
};
void test_1(int *v)
{
    (void)v;
    std::cout << "pointer\n";
};

template <typename T>
auto sum(const std::vector<T> &v) -> T
{
    T sum{0};
    for (const auto i : v)
    {
        sum += i;
    }
    return sum;
}

template <typename T>
auto sum_algorithm(const std::vector<T> &v) -> T
{
    return std::accumulate(v.begin(), v.end(), static_cast<T>(0)); // add cast!
}

template <typename T>
void test(const std::vector<T> &v, std::string_view typeName)
{
    std::cout << "!@!@ START for [" << typeName << "] !@\n";
    std::cout << "\t" << sum(v) << "\n";
    std::cout << "\t" << sum_algorithm(v) << "\n";
    std::cout << "!@!@ END !@\n";
}

template <typename T>
void default_test(std::string_view typeName)
{

    test(std::vector<T>{std::numeric_limits<T>::max(), static_cast<T>(1)}, typeName);
}

#define TEST_FOR_MACRO(TypeName) \
    default_test<TypeName>(#TypeName);

int main()
{
    TEST_FOR_MACRO(uint8_t);
    TEST_FOR_MACRO(uint16_t);
    TEST_FOR_MACRO(uint32_t);
    TEST_FOR_MACRO(uint64_t);

    TEST_FOR_MACRO(int8_t);
    TEST_FOR_MACRO(int16_t);
    TEST_FOR_MACRO(int32_t);
    TEST_FOR_MACRO(int64_t);

    TEST_FOR_MACRO(signed char);
    TEST_FOR_MACRO(unsigned char);
    TEST_FOR_MACRO(short);
    TEST_FOR_MACRO(short int);
    TEST_FOR_MACRO(signed short);
    TEST_FOR_MACRO(signed short int);
    TEST_FOR_MACRO(unsigned short);
    TEST_FOR_MACRO(unsigned short int);
    TEST_FOR_MACRO(int);
    TEST_FOR_MACRO(signed);
    TEST_FOR_MACRO(signed int);
    TEST_FOR_MACRO(unsigned);
    TEST_FOR_MACRO(unsigned int);
    TEST_FOR_MACRO(long);
    TEST_FOR_MACRO(long int);
    TEST_FOR_MACRO(signed long);
    TEST_FOR_MACRO(signed long int);
    TEST_FOR_MACRO(unsigned long);
    TEST_FOR_MACRO(unsigned long int);
    TEST_FOR_MACRO(long long);
    TEST_FOR_MACRO(long long int);
    TEST_FOR_MACRO(signed long long);
    TEST_FOR_MACRO(signed long long int);
    TEST_FOR_MACRO(unsigned long long);
    TEST_FOR_MACRO(unsigned long long int);

    std::cout << "IF CONSTEXPR " << static_cast<int>(INT_SIZE) << "\n";
    std::cout << "IntDefaultT " << static_cast<int>(INT_SIZE_2) << "\n";
    default_int i = 0;
    std::cout << " function dispatch \n";
    test_1(i);
    int *a{nullptr};
    std::cout << "sizeof(a) = " << sizeof(a) << "\n";
    std::cout << "sizeof(*a) = " << sizeof(*a) << "\n";
    std::cout << "sizeof(&a) = " << sizeof(&a) << "\n";

    std::cout << "SIZEOF = " << get_int_size_c() << "\n";
    delete a;
}
