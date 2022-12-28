#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>


#include "checker.h"

class Wordle {
    private:
        std::string path_;
        std::ifstream is_;
        std::vector<std::pair<char, bool>> state_;
        std::vector<std::vector<std::pair<char, bool>>> past_states_;
        std::vector<std::string> bank_;
        std::vector<char> null_chars_;

        int tries_ = 0;
        
        const std::string ALPHABEBET = "abcdefghijklmnopqrstuvwxyz";
    public:
        Wordle();
        Wordle(const std::vector<std::pair<char, bool>> & state) : state_(state){};

        //provides file to use for wordbank
        bool SetBank(const std::string &);

        //getters
        std::vector<std::pair<char, bool>> GetState();
        int GetTries();

        //control flow
        void UpdateState(const std::vector<std::pair<char, bool>> & word);
        std::string BestGuess(std::vector<char> &);
        std::vector<std::string> FillsConstraints();
        bool PassConstraints(std::string);
        bool HasNullChars(std::string);
        bool OffPosition(std::string, int);


};