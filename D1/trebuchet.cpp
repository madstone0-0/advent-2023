#include <cstddef>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "utils.hpp"

using namespace utils;
using std::cout, std::cin, std::endl, std::optional, std::string;

const static std::unordered_map<string, int> nums{{"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
                                                  {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

optional<int> findAlphaNumFromIndex(const string& line, const size_t& index = 0) {
    size_t number{};

    for (const auto& [key, val] : nums) {
        string checked{line.substr(index, key.size())};
        if (checked == key) {
            number = val;
            break;
        }
    }

    if (number == 0)
        return std::nullopt;
    else
        return number;
}

int findNumber(const string& line) {
    auto firstNum{-1};
    auto tempNum{0};
    auto lastNum{0};
    size_t i{};

    for (; i != line.size(); i++) {
        auto number{findAlphaNumFromIndex(line, i)};
        if (number.has_value() && firstNum == -1) firstNum = number.value();

        if (number.has_value()) tempNum = number.value();

        const string& c{line.at(i)};
        if (std::isdigit(line.at(i))) {
            auto cInt{std::stoi(c)};
            if (firstNum == -1) firstNum = cInt;
            tempNum = cInt;
        }
    }

    lastNum = tempNum;
    return std::stoi(std::to_string(firstNum) + std::to_string(lastNum));
}

int main() {
    size_t sum{};
    string inputPath{"/home/mads/projects/Advent/D1/input.txt"};
    auto file = open(inputPath);
    auto lines{splitLines(file)};
    size_t i{};
    for (const auto& line : lines) {
        sum += findNumber(line);
        i++;
    }
    cout << sum << endl;
}
