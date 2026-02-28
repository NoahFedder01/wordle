#include "word.h"
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

vector<Word> initializeWithRatings(string filename) {
    ifstream file(filename);  // Open file
    if (!file) {                              // Handle errors opening file
        cerr << "Error opening file" << endl; 
    }

    vector<Word> words;  // Prepare vector to be filled
    string line;

    while (getline(file, line)) {   // Read entire line
        stringstream ss(line);
        string word;
        double rating;

        // Extract word and rating from the stringstream
        if (getline(ss, word, ',') && ss >> rating) {
            words.push_back(Word(word, rating)); // Push parsed word & rating
        } else {
            cerr << "Invalid line format: " << line << endl;
        }
    }

    return words;
}

int main() {

    vector<Word> wordSet = initializeWithRatings("efficientSorted.txt");

    cout << "What word would you like to check for the first guess?" << endl;

    string ans;

    cin >> ans;

    while (ans.size() != 5) {
        cout << "The word must be five letters long, try again:" << endl;
        cin >> ans;
    }

    int n = wordSet.size(), selected = -1;
    
    for (int i = 0; i < n; i++) {
        if (wordSet[i].word == ans) {
            selected = i;
            break;
        }
    }

    if (selected == -1) {
        cout << "Error, word not found." << endl;
        return 0;
    }

    // cout << "Word: " << wordSet[selected].word << ", rating: " << wordSet[selected].rating << endl;

    cout << "With " << wordSet[selected].word << ", " << (1 - pow(0.5, wordSet[selected].rating)) * 100 << "% of the solution space is cut out on average on the first guess." << endl;

    
    return 0;
}