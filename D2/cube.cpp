#include <re2/re2.h>

#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <cstdio>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace std;
using namespace utils;
namespace algo = boost::algorithm;

const static int RED{12};
const static int BLUE{14};
const static int GREEN{13};

static const RE2 gameIdRegex{"Game (\\d+)"};
static const RE2 blueRegex{"(\\d+) blue"};
static const RE2 redRegex{"(\\d+) red"};
static const RE2 greenRegex{"(\\d+) green"};

int findMatchingGameId(const string& line) {
    int gameId{-1};

    vector<string> tokens;
    algo::split(tokens, line, [](auto c) { return c == ';'; });
    bool nope{};
    ranges::for_each(tokens, [&nope](auto pull) {
        string redStr;
        string blueStr;
        string greenStr;

        RE2::PartialMatch(pull, redRegex, &redStr);
        RE2::PartialMatch(pull, greenRegex, &greenStr);
        RE2::PartialMatch(pull, blueRegex, &blueStr);

        if (!redStr.empty())
            if (stoi(redStr) > RED) nope = true;

        if (!greenStr.empty())
            if (stoi(greenStr) > GREEN) nope = true;

        if (!blueStr.empty())
            if (stoi(blueStr) > BLUE) nope = true;
    });

    if (nope) return gameId;

    string gameIdStr{};
    RE2::PartialMatch(line, gameIdRegex, &gameIdStr);
    gameId = stoi(gameIdStr);
    return gameId;
}

int findMinCubes(const string& line) {
    int redMax{};
    int blueMax{};
    int greenMax{};

    re2::StringPiece input{line};

    string value{};
    while (RE2::FindAndConsume(&input, redRegex, &value)) {
        int val{stoi(value)};
        if (val > redMax) redMax = val;
    }

    input = line;
    while (RE2::FindAndConsume(&input, blueRegex, &value)) {
        int val{stoi(value)};
        if (val > blueMax) blueMax = val;
    }

    input = line;
    while (RE2::FindAndConsume(&input, greenRegex, &value)) {
        int val{stoi(value)};
        if (val > greenMax) greenMax = val;
    }

    return redMax * blueMax * greenMax;
}

int main() {
    size_t part1{};
    size_t part2{};
    string inputPath{"/home/mads/projects/Advent/D2/input.txt"};
    auto file = open(inputPath);
    auto lines{splitLines(file)};
    for (const auto& line : lines) {
        auto id{findMatchingGameId(line)};
        if (id == -1) continue;
        part1 += id;
    }

    for (const auto& line : lines) {
        part2 += findMinCubes(line);
    }
    cout << "Part 1: " << part1 << "\n";
    cout << "Part 2: " << part2 << endl;
}
