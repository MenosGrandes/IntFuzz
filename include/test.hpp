#include <vector>
#include "sizeof.hpp"
#ifndef TEST_HPP
#define TEST_HPP


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

void run_tests()
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
}
#endif