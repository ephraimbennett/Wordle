#include "checker.h"

using std::vector;
using std::string;
using std::pair;

using std::cout;
using std::endl;

vector<pair<char, bool>> Checker::Test(string guess, vector<char> & null_chars) {

    vector<pair<char, bool>> res;
    if (guess == answer_) {
        res.push_back({'1', true});
        return res;
    }

    for (int i = 0; i < 5; i++) {
        res.push_back({' ', false});
    }

    string answer_copy;
    string guess_copy;
    
    for (int i = 0; i < 5; i++) {
        char c1 = guess.at(i);
        char c2 = answer_.at(i);
        if (c1 == c2) {
            res.at(i) = {c1, true};
        } else {
            answer_copy.push_back(c2);
            guess_copy.push_back(c1);
        }
    }

    for (int i = 0; i < answer_.length(); i++) {
        if (res.at(i).second) continue;
        char c = guess.at(i);
        if (answer_copy.find(c) != string::npos) {
            res.at(i) = {c, false};
        } else {
            res.at(i) = {' ', false};
            if (std::find(null_chars.begin(), null_chars.end(), c) == null_chars.end()) {
                if (answer_.find(c) == string::npos) {
                    null_chars.push_back(c);
                }
            }
        }
        
    }
    return res;
}

void Checker::SetAnswer(string answer) {
    answer_ = answer;
}

/*int main() {
    Checker checker("arbma");
    vector<char> null_chars;
    vector<pair<char, bool>> state = checker.Test("abaca", null_chars);
    for (auto x : state) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    return 0;
}*/