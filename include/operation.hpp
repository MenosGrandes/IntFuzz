#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>
#ifndef OPERATION_HPP
#define OPERATION_HPP
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
#endif