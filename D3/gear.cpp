#include <re2/re2.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace std;
using namespace utils;
namespace rg = std::ranges;

const static set<char> SYMBOLS{'*', '%', '+', '=', '$', '@', '&', '/', '#', '-'};
const static RE2 numRegex{"(\\d{1,3})"};

int findNum(const vector<char>& range) {
    auto res{-1};
    string tempStr{};
    RE2::PartialMatch(string{range.begin(), range.end()}, numRegex, &tempStr);

    if (!tempStr.empty()) res = stoi(tempStr);
    return res;
}

vector<int> findPartNums(const vector<vector<char>>& lines, const char& c, const int& col, const int& row) {
    auto numRows{lines.size() - 1};
    auto numCols{lines.at(0).size() - 1};

    vector<int> nums{};
    auto up{row - 1 >= 0 ? row - 1 : 0};
    auto down{row + 1 < numRows + 1 ? row + 1 : numRows};
    auto left{col - 1 >= 0 ? col - 1 : 0};
    auto right{col + 1 < numCols + 1 ? col + 1 : numCols};
    pair<int, int> diagTopR{row - 1 >= 0 ? row - 1 : 0, col + 1 < numCols + 1 ? col + 1 : numCols};
    pair<int, int> diagTopL{row - 1 >= 0 ? row - 1 : 0, col - 1 >= 0 ? col - 1 : 0};
    pair<int, int> diagBtmR{row + 1 < numRows + 1 ? row + 1 : numRows, col + 1 < numCols + 1 ? col + 1 : numCols};
    pair<int, int> diagBtmL{row + 1 < numRows + 1 ? row + 1 : numRows, col - 1 >= 0 ? col - 1 : 0};

    const auto topEmpty = row != 0 ? lines.at(row - 1).at(col) == '.' : false;
    const auto btmEmpty = row != numRows ? lines.at(row + 1).at(col) == '.' : false;
    if ((isdigit(lines.at(up).at(col)) != 0)) {
        string temp{lines.at(up).begin(), lines.at(up).end()};
        auto upLim{temp.find('.', col) != string::npos ? temp.find('.', col) : temp.size()};
        auto lowLim{temp.rfind('.', col) != string::npos ? temp.rfind('.', col) : 0};
        auto res = findNum(vector<char>{lines.at(up).begin() + lowLim, lines.at(up).begin() + upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(down).at(col)) != 0) {
        string temp{lines.at(down).begin(), lines.at(down).end()};
        auto upLim{temp.find('.', col) != string::npos ? temp.find('.', col) : temp.size()};
        auto lowLim{temp.rfind('.', col) != string::npos ? temp.rfind('.', col) : 0};

        auto res = findNum(vector<char>{lines.at(down).begin() + lowLim, lines.at(down).begin() + upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(diagTopR.first).at(diagTopR.second)) != 0 && topEmpty && row != 0) {
        const auto& diagCol = diagTopR.second;
        const auto& diagRow = diagTopR.first;

        string temp{lines.at(diagRow).begin(), lines.at(diagRow).end()};
        auto upLim{temp.find('.', diagCol) != string::npos ? temp.find('.', diagCol) : temp.size()};
        auto lowLim{temp.rfind('.', diagCol) != string::npos ? temp.rfind('.', diagCol) : 0};

        auto res = findNum(vector<char>{lines.at(diagRow).begin() + lowLim, lines.at(diagRow).begin() + upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(diagBtmR.first).at(diagBtmR.second)) != 0 && btmEmpty && row != numRows) {
        const auto& diagCol = diagBtmR.second;
        const auto& diagRow = diagBtmR.first;

        string temp{lines.at(diagRow).begin(), lines.at(diagRow).end()};
        auto upLim{temp.find('.', diagCol) != string::npos ? temp.find('.', diagCol) : temp.size()};
        auto lowLim{temp.rfind('.', diagCol) != string::npos ? temp.rfind('.', diagCol) : 0};

        auto res = findNum(vector<char>{lines.at(diagRow).begin() + lowLim, lines.at(diagRow).begin() + upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(diagTopL.first).at(diagTopL.second)) != 0 && topEmpty && row != 0) {
        const auto& diagCol = diagTopL.second;
        const auto& diagRow = diagTopL.first;

        string temp{lines.at(diagRow).begin(), lines.at(diagRow).end()};
        auto upLim{temp.find('.', diagCol) != string::npos ? temp.find('.', diagCol) : temp.size()};
        auto lowLim{temp.rfind('.', diagCol) != string::npos ? temp.rfind('.', diagCol) : 0};

        auto res = findNum(vector<char>{lines.at(diagRow).begin() + lowLim, lines.at(diagRow).begin() + upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(diagBtmL.first).at(diagBtmL.second)) != 0 && btmEmpty && row != numRows) {
        const auto& diagCol = diagBtmL.second;
        const auto& diagRow = diagBtmL.first;

        string temp{lines.at(diagRow).begin(), lines.at(diagRow).end()};
        auto upLim{temp.find('.', diagCol) != string::npos ? temp.find('.', diagCol) : temp.size()};
        auto lowLim{temp.rfind('.', diagCol) != string::npos ? temp.rfind('.', diagCol) : 0};

        auto res = findNum(vector<char>{lines.at(diagRow).begin() + lowLim, lines.at(diagRow).begin() + upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(row).at(right)) != 0) {
        auto upLim{lines.at(row).begin() + right + 3 < lines.at(row).end() ? lines.at(row).begin() + right + 3
                                                                           : lines.at(col).end()};
        auto res = findNum(vector<char>{lines.at(row).begin() + right, upLim});
        if (res != -1) nums.push_back(res);
    }

    if (isdigit(lines.at(row).at(left)) != 0) {
        auto upLim{lines.at(row).begin() + left + 3 < lines.at(row).end() ? lines.at(row).begin() + left + 3
                                                                          : lines.at(row).end()};
        auto lowLim{lines.at(row).begin() + col - 3 >= lines.at(row).begin() ? lines.at(row).begin() + col - 3
                                                                             : lines.at(row).begin()};
        auto res = findNum(vector<char>{lowLim, upLim});
        if (res != -1) nums.push_back(res);
    }

    return nums;
}

struct Res {
    long part1{};
    long part2{};
};

Res findPartSum(const vector<vector<char>>& lines) {
    long part1{};
    long part2{};
    vector<int> resNums;
    for (size_t row{}; row < lines.size(); row++) {
        for (size_t col{}; col < lines.at(0).size(); col++) {
            try {
                auto c{lines.at(row).at(col)};

                if (SYMBOLS.find(c) != SYMBOLS.end()) {
                    auto nums = findPartNums(lines, c, col, row);
                    if (c == '*' && nums.size() == 2) {
                        part2 += nums.front() * nums.back();
                    }
                    resNums.insert(resNums.end(), nums.begin(), nums.end());
                }

            } catch (const std::exception& e) {
                cout << e.what() << endl;
                cout << "row: " << row << " col: " << col << endl;
            }
        }
    }
    rg::for_each(resNums, [&part1](auto i) { part1 += i; });
    return {part1, part2};
}

int main() {
    string inputPath{"/home/mads/projects/Advent/D3/input.txt"};
    auto file = open(inputPath);
    string line;
    vector<vector<char>> lines;
    while (getline(file, line)) {
        lines.emplace_back(line.begin(), line.end());
    }
    const auto& [part1, part2] = findPartSum(lines);
    cout << "Part 1: " << part1 << "\n";
    cout << "Part 2: " << part2 << endl;
}
