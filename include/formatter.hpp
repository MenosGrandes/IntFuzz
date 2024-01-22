#ifndef FORMATTER_HPP
#define FORMATTER_HPP
#include <iostream>
#define P_FORMAT_BEGIN_N(N) std::cout << std::setw(N) << std::right
#define P_FORMAT_BEGIN P_FORMAT_BEGIN_N(30)
#define P_FORMAT_BEGIN_T P_FORMAT_BEGIN_N(1)
#define P_FORMAT_BEGIN_V P_FORMAT_BEGIN_N(1)
#define P_FORMAT_BEGIN_V_2 P_FORMAT_BEGIN_N(1)
#endif