#include "wordle.h"

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::string;
using std::vector;
using std::pair;

Wordle::Wordle() {
    vector<pair<char, bool>> s;
    for (size_t i = 0; i < 5; i++) {//fills w/empty
        s.push_back({' ', false});
    }
    state_ = s;
}

bool Wordle::SetBank(const std::string & path) {
    is_.open(path);
    string x;
    while (getline(is_, x)) {
        bank_.push_back(x);
    }
    is_.close();
    return is_.is_open();
}


vector<pair<char, bool>> Wordle::GetState() {
    return state_;
}

int Wordle::GetTries() {
    return tries_;
}

void Wordle::UpdateState(const vector<pair<char, bool>> & state) {
    state_ = state;
}

bool Wordle::OffPosition(string word, int idx) {
    char c = state_.at(idx).first;
    //first check that char is not located at this specific location
    if (word.at(idx) == c) return false;

    //next check that it exists somewhere else
    for (int i = 0; i < word.length(); i++) {
        if (!state_.at(i).second) {
            if (word.at(i) == c) {
                return true;
            }
        }
    }
    return false;
}

bool Wordle::PassConstraints(string word) {
    for (int i = 0; i < state_.size(); i++) {
        if (state_.at(i).second) {//if the character is at this position
            if (state_.at(i).first != word.at(i)) {
                return false;
            }
        } else if (state_.at(i).first != ' ') {//if character isn't at this position
            if (!OffPosition(word, i)) {
                return false;
            }
        }
    }
    return true;
}

bool Wordle::HasNullChars(std::string word) {
    for (char c : word) {
        if (std::find(null_chars_.begin(), null_chars_.end(), c) != null_chars_.end()) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> Wordle::FillsConstraints() {

    vector<string> res;
    for (const auto & word : bank_) {
        if (PassConstraints(word) && HasNullChars(word)) {
            res.push_back(word);
        }
    }

    return res;
}

std::string Wordle::BestGuess(std::vector<char> & null_chars) {
    tries_++;
    
    null_chars_ = null_chars;
    vector<string> v = FillsConstraints();
    bank_ = v;
    cout << v.size() << endl;
    return v.at(v.size() / 2);
}

int main() {
    vector<pair<char, bool>> state;
    for (int i = 0; i < 5; i++) {
        state.push_back({' ', false});
    }
    state.at(0) = {'m', false};
    state.at(1) = {'i', false};
    state.at(2) = {'l', false};
    state.at(3) = {'e', true};
    state.at(4) = {' ', false};
    vector<char> null_chars;
    null_chars.push_back('a');
    null_chars.push_back('r');
    null_chars.push_back('o');
    null_chars.push_back('s');
    for (auto x : state) {
        cout << x.first << " " << x.second << endl;
    }
    
    Wordle w;
    w.SetBank("valid-wordle-words.txt");
    w.UpdateState(state);
    cout << w.BestGuess(null_chars) << endl;
    
}

/*int main() {

    cout << std::boolalpha;

    Wordle w;
    w.SetBank("valid-wordle-words.txt");

    vector<char> null_chars;

    Checker c("upset");

    string guess = "babys";
    
    vector<pair<char, bool>> state = c.Test(guess, null_chars);
    while (state.at(0).first != '1') {

        //print state
        cout << "State:" << endl;
        for (auto x : w.GetState()) {
            cout << x.first << " " << x.second << endl;
        }

        //print bad chars
        cout << "Chars:" << endl;
        for (auto x : null_chars) {
            cout << x << " ";
        }

        cout << endl;
        cout << guess << endl;
        w.UpdateState(state);
        guess = w.BestGuess(null_chars);
        cout << guess << endl;
        state = c.Test(guess, null_chars);
        
    }
    cout << w.GetTries() << endl;
    

    return 0;
}*/