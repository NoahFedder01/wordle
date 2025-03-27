#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Word {
    public:
        string word;            // Stores the word
        double rating;          // Stores value assaociated with word (some measure of probability)

        Word() : word(""), rating(0.0) {}
        Word(string word) : word(word) {}                                  // Constructor for only word
        Word(string word, double rating) : word(word), rating(rating) {}   // Constructor for both, just in case
};

class ParameterHolder {
    public:
        Word word;
        vector<char> params;

        ParameterHolder(Word word, vector<char> params) : word(word), params(params) {}
};

#endif