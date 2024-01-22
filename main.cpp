#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>
#include "include/default_int.hpp"
#include "include/operation.hpp"
#include "include/test.hpp"
#include "include/timer.hpp"

int main() {
    
    run_tests();
    P_FORMAT_BEGIN_T << "\n";
    P_FORMAT_BEGIN_T << "IF CONSTEXPR int size = ["
                     << static_cast<int>(INT_SIZE) << "]\n";
    P_FORMAT_BEGIN_T << "IntDefaultT int size = ["
                     << static_cast<int>(INT_SIZE_2) << "]\n";
    default_int i = 0;
    P_FORMAT_BEGIN_T << "function dispatch ";
    test_1(i);
    P_FORMAT_BEGIN_T << "\n";


    run_examaple();
    return 0;
}