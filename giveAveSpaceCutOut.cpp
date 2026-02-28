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

    int n = wordSet.size(), sum = 0;

    for (int i = 0; i < n; i++) {
        sum += wordSet[i].rating;
    }

    // Debug line bc I used n instead of i :-P
    // cout << "Total sum is: " << sum << endl;

    sum /= n;

    cout << "On average, " << (1 - pow(0.5, sum)) * 100 << "% of the solution space is cut out." << endl;
    
    return 0;
}