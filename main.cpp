#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

template <typename T>
struct SizeOfT_t {
    static constexpr std::tuple<int, int> size =
        std::make_tuple(sizeof(T), std::numeric_limits<T>::digits);
};
template <typename T>
static constexpr auto size_v = SizeOfT_t<T>::size;

enum class IntDefaultE : std::int8_t {
    INT_8 = 8,
    INT_16 = 16,
    INT_32 = 32,
    INT_64 = 64,
    UNDEFINED = 0
};

constexpr auto get_int_type() {
    if constexpr (size_v<int> == size_v<int8_t>) {
        return IntDefaultE::INT_8;
    } else if (size_v<int> == size_v<int16_t>) {
        return IntDefaultE::INT_16;
    } else if (size_v<int> == size_v<int32_t>) {
        return IntDefaultE::INT_32;
    } else if (size_v<int> == size_v<int64_t>) {
        return IntDefaultE::INT_64;
    } else {
        return IntDefaultE::UNDEFINED;
    }
}

template <typename T, typename Enabler = void>
struct IntDefaultT : std::false_type {};

template <typename T>
struct IntDefaultT<T, typename std::enable_if_t<std::is_same_v<int, T>>>
    : std::true_type {
    using default_int_t = T;
};
template <typename T>
using int_default_t = typename IntDefaultT<T>::default_int_t;

template <typename T>
static constexpr auto int_default_v = IntDefaultT<T>::value;

constexpr auto get_int_type_2() {
    if constexpr (int_default_v<int8_t>) {
        return IntDefaultE::INT_8;
    } else if (int_default_v<int16_t>) {
        return IntDefaultE::INT_16;
    } else if (int_default_v<int32_t>) {
        return IntDefaultE::INT_32;
    } else if (int_default_v<int64_t>) {
        return IntDefaultE::INT_64;
    } else {
        return IntDefaultE::UNDEFINED;
    }
}

template <typename...>
struct is_one_of : std::false_type {};

template <typename... T>
static constexpr auto is_one_of_v = is_one_of<T...>::value;
template <typename F, typename S, typename... T>
struct is_one_of<F, S, T...> {
    static constexpr bool value = std::is_same_v<F, S> || is_one_of_v<F, T...>;
    using type = F;
};

using default_int_t = is_one_of<int, int8_t, int64_t, int32_t, int16_t>;
using default_int = default_int_t::type;

static constexpr auto INT_SIZE = get_int_type();
static constexpr auto INT_SIZE_2 = get_int_type_2();

#define P_FORMAT_BEGIN_N(N) std::cout << std::setw(N) << std::right
#define P_FORMAT_BEGIN P_FORMAT_BEGIN_N(30)
#define P_FORMAT_BEGIN_T P_FORMAT_BEGIN_N(1)
#define P_FORMAT_BEGIN_V P_FORMAT_BEGIN_N(1)
#define P_FORMAT_BEGIN_V_2 P_FORMAT_BEGIN_N(1)

void test_1(int64_t v) {
    (void)v;
    P_FORMAT_BEGIN << "int = [64]";
};
void test_1(int32_t v) {
    (void)v;
    P_FORMAT_BEGIN << "int = [32]";
};
void test_1(int16_t v) {
    (void)v;
    P_FORMAT_BEGIN << "int = [16]";
};
void test_1(int8_t v) {
    (void)v;
    P_FORMAT_BEGIN << "int = [8]";
};
void test_1(int *v) {
    (void)v;
    P_FORMAT_BEGIN << "int = [pointer]";
};
namespace cast {
template <typename T>
auto sum(const std::vector<T> &v) -> T {
    T sum{0};
    for (const auto &i : v) {
        sum += i;
    }
    return sum;
}
template <typename T>
auto mul(const std::vector<T> &v) -> T {
    T value = v[0];
    for (auto i = 1; i < v.size(); i++) {
        value *= v[i];
    }
    return value;
}
template <typename T, typename Operator>
auto operate(const std::vector<T> &v, Operator op) -> T {
    T value = v[0];
    for (auto i = 1; i < v.size(); i++) {
        value = op( value, v[i]);
    }
    return value;
}
template <typename T>
auto sum_algorithm(const std::vector<T> &v) -> T {
    return std::accumulate(v.cbegin(), v.cend(),
                           static_cast<T>(0));  // add cast!
}
}  // namespace cast
namespace non_cast {
template <typename T>
auto sum(const std::vector<T> &v) -> T {
    T sum = 0;
    for (const auto &i : v) {
        sum += i;
    }
    return sum;
}

template <typename T>
auto sum_algorithm(const std::vector<T> &v) -> T {
    return std::accumulate(v.cbegin(), v.cend(), 0);
}
}  // namespace non_cast
template <typename T>
void test_sizeof() {
    T t{T{}};
    T *t_ptr{nullptr};
    P_FORMAT_BEGIN << " sizeof(T) = " << sizeof(t) << "\n";
    P_FORMAT_BEGIN << " sizeof t_ptr = " << sizeof(t_ptr) << "\n";
    P_FORMAT_BEGIN << " sizeof *t_ptr = " << sizeof(*t_ptr) << "\n";
    P_FORMAT_BEGIN << " sizeof &t_ptr = " << sizeof(&t_ptr) << "\n";
}
template <typename T>
void test(const std::vector<T> &v, const char *typeName) {
    P_FORMAT_BEGIN_T << "[" << typeName << "]\n";
    P_FORMAT_BEGIN_N(31) << "vector = [";
    for (const T &value : v) {
        std::cout << value << " ";
    }
    std::cout << "]\n";
    /*OPERATORS */
    P_FORMAT_BEGIN << " cast::operate plus = "
                   << cast::operate(v, std::plus<T>{}) << "\n";
    P_FORMAT_BEGIN << " cast::operate minus = "
                   << cast::operate(v, std::minus<T>{}) << "\n";
    P_FORMAT_BEGIN << " cast::operate multiplies = "
                   << cast::operate(v, std::multiplies<T>{}) << "\n";
    P_FORMAT_BEGIN << " cast::operate divides = "
                   << cast::operate(v, std::divides<T>{}) << "\n";
    P_FORMAT_BEGIN << " cast::operate modulus = "
                   << cast::operate(v, std::modulus<T>{}) << "\n";

    /*OPERATORS*/
    P_FORMAT_BEGIN << " cast::sum = " << cast::sum(v) << "\n";
    P_FORMAT_BEGIN << " cast::sum_algorithm = " << cast::sum_algorithm(v)
                   << "\n";
    P_FORMAT_BEGIN << " cast::mul = " << cast::mul(v) << "\n";


    P_FORMAT_BEGIN << " nocast::sum = " << non_cast::sum(v) << "\n";
    P_FORMAT_BEGIN << " nocast::sum_algorithm = " << non_cast::sum_algorithm(v)
                   << "\n";

    test_sizeof<T>();
    P_FORMAT_BEGIN_T << "\n";
}

template <typename T>
void default_test(const char *typeName) {
    test(std::vector<T>{std::numeric_limits<T>::max(), static_cast<T>(2)},
         typeName);
}

#define TEST_FOR_MACRO(TypeName) default_test<TypeName>(#TypeName);

int main() {

    
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

    P_FORMAT_BEGIN_T << "\n";

    P_FORMAT_BEGIN_T << "IF CONSTEXPR int size = ["
                     << static_cast<int>(INT_SIZE) << "]\n";
    P_FORMAT_BEGIN_T << "IntDefaultT int size = ["
                     << static_cast<int>(INT_SIZE_2) << "]\n";
    default_int i = 0;
    P_FORMAT_BEGIN_T << "function dispatch ";
    test_1(i);
    P_FORMAT_BEGIN_T << "\n";

    return 0;
}
