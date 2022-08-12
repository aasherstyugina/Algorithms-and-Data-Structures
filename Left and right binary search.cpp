#include <iostream>
#include <vector>

int leftBound(const std::vector<int>& numbers, int request) {
    int left = -1;
    int right = numbers.size();
    while (left < right - 1) {
        int mid = left + (right - left) / 2;
        if (numbers[mid] < request) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (right >= 0 && right < numbers.size() && numbers[right] == request) {
        return right;
    } else {
        return -1;
    }
}

int rightBound(const std::vector<int>& numbers, int request) {
    int left = -1;
    int right = numbers.size();
    while (left < right - 1) {
        int mid = left + (right - left) / 2;
        if (numbers[mid] <= request) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (left >= 0 && left < numbers.size() && numbers[left] == request) {
        return left;
    } else {
        return -1;
    }
}

int main() {
    int count_of_numbers, count_of_requests;
    std::cin >> count_of_numbers >> count_of_requests;
    std::vector<int> numbers;
    for (int i = 0; i < count_of_numbers; ++i) {
        int number;
        std::cin >> number;
        numbers.push_back(number);
    }

    for (int i = 0; i < count_of_requests; ++i) {
        int request;
        std::cin >> request;
        int left = leftBound(numbers, request) + 1;
        int right = rightBound(numbers, request) + 1;
        if (left * right == 0) {
            std::cout << "0" << '\n';
        } else {
            std::cout << left << " " << right << '\n';
        }
    }

    return 0;
}
