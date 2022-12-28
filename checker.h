#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

class Checker {
    private:
        std::string answer_;
    public:
        Checker() = default;
        Checker(std::string answer) : answer_(answer){};
        void SetAnswer(std::string);
        std::vector<std::pair<char, bool>> Test(std::string, std::vector<char> &);
};