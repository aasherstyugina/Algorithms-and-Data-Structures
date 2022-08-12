#include <iostream>
#include <cmath>
#include <iomanip>

double const kEpsilon = 0.000000001;

double func(double root) {
    return std::pow(root, 2) + std::sqrt(root);
}

double binarySearch(double result) {
    double left = 0;
    double right = result;

    while (right - left > kEpsilon) {
        double mid = left + (right - left) / 2;
        double current_result = func(mid);
        if (std::abs(result - current_result) <= kEpsilon) {
            return mid;
        }
        if (current_result <= result) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

int main() {
    double result;
    std::cin >> result;

    std::cout << std::fixed << std::setprecision(9) << binarySearch(result);

    return 0;
}
