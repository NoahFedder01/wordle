#include "word.h"
#include <vector>
#include <fstream>
#include <random>

using namespace std;

/*
init creates the original Word object vector with just the words, and no ratings
It does this by parsing the word-list.txt file
*/
vector<Word> init(string filename) {
    ifstream file(filename);     // Open file
    if (!file) {                        // Handle errors opening file
        cerr << "Error opening file" << endl;
    }
    string line;       // Parsing variable
    vector<Word> words;     // Prepare vector to be filled
    while (getline(file,line)) {    // Parse txt
        words.push_back(Word(line));    // Create Word object for each word, push to back of vector
    }
    return words;
}

/*
assess gives you the value (i.e. green, yellow, neither)
of each letter in your word

PROBLEMS:
Something but idk what
*/
void assess(string guess, string answer) {
    int mapping[5][5] = {       // 5x5 mapping of guess to answer
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    for (int i = 0; i < 5; i++) {           // if guess[i] == answer[j], 0 becomes 1, if i == j too, 0 becomes 2
        for (int j = 0; j < 5; j++) {
            if (guess[i] == answer[j]) {
                mapping[i][j] = 1;
                if (i == j) {
                    mapping[i][j] = 2;
                }
            }
        }
    }

    for (int i = 0; i < 5; i++) {       // Prune 1s on the same column / row as 2s
        if (mapping[i][i] == 2) {
            for (int j = 0; j < 5; j++) {
                if (i != j) {
                    mapping[i][j] = 0;
                    mapping[j][i] = 0;
                }
            }
        }
    }

    for (int i = 0; i < 5; i++) {       // Prune 1s on the same column / row as 1s
        for (int j = 0; j < 5; j++) {
            if (mapping[i][j] == 1) {
                for (int n = 0; n < 5; n++) {
                    for (int m = 0; m < 5; m++) {
                        if (!(n == i && m == j)) {
                            if (n == i || m == j) {
                                mapping[n][m] = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    // for (int i = 0; i < 5; i++) {        // For debugging, lets you see the finished 5x5 matrix
    //     for (int j = 0; j < 5; j++) {
    //         cout << mapping[j][i] << " ";
    //     }
    //     cout << endl;
    // }

    char placehold = 'N';

    cout << endl;

    for (int i = 0; i < 5; i++) {
        placehold = 'N';
        for (int j = 0; j < 5; j++) {
            if (mapping[i][j] == 1 && placehold != 'G') {
                placehold = 'Y';
            } else if (mapping[i][j] == 2) {
                placehold = 'G';
            }
        }
        cout << placehold << " ";
    }

    cout << endl << endl;
    return;
}

/*
Just checks if the guess is in the Word vector
*/
bool isValidWord(string guess, vector<Word> myWords) {
    for (int i = 0; i < myWords.size(); i++) {
        if (guess == myWords[i].word) {
            return true;
        }
    }
    return false;
}

// /*
// Bit algorithm: brute force calculate FOR EVERY WORD how many 
// other words would be cut out of the pool if
// (ex for crane):
// crane
// N N N N N
// or
// crane
// Y N N N N
// or
// crane
// Y N Y G Y

// were the result of the guess (125 possibilities per word)

// UNDER CONSTRUCTION
// */
// vector<Word> giveRating(vector<Word> myWords) {
//     vector<int> myState = {0,0,0,0,0};
//     for (int i = 0; i < myWords.size(); i++) {
//         for (int j = 0; j < myWords.size(); j++) {
//             for (int bT = 0; bT < 125; bT++) {
                
//             }
//         }
//     }
//     return myWords;
// }

// /*
// incrementBaseThree
// */
// vector<int> incrementBaseThree(vector<int> input) {
//     if (input == vector<int>{2,2,2,2,2}) {
//         return vector<int>{0,0,0,0,0};
//     }
//     int baseTen = input[4]*1 + input[3]*3 + input[2]*9 + input[1]*27 + input[0]*81;
//     baseTen++;

//     if (baseTen >= 81) {
//         input[0] = baseTen / 81;
//         baseTen %= 81;
//     }
//     if (baseTen >= 27) {
//         input[1] = baseTen / 27;
//         baseTen %= 27;
//     }
//     if (baseTen >= 9) {
//         input[2] = baseTen / 9;
//         baseTen %= 9;
//     }
//     if (baseTen >= 3) {
//         input[3] = baseTen / 3;
//         baseTen %= 3;
//     }
//     input[4] = baseTen;

//     return input;
// }

// /*
// Does it work:
// determines if a word can work with the given set of restrictions

// UNDER CONSTRUCTION
// */
// bool doesItWork(Word guess, Word check, vector<char> params) {
//     for (int i = 0; i < 5; i++) {
//         if (params[i] == 'G') {                         // If parameter is Green, check if both words have the same letter in that spot
//             if (guess.word[i] == check.word[i]) {
//                 continue;
//             }
//             return false;       // Parameter i is Green, but letters i in guess and check do not correspond
//         }
//         if (params[i] == 'Y') {

//         }
//     }
//     return true;
// }


int main() {
    vector<Word> allWords = init("word-list.txt");
    vector<Word> myWords = init("wordle-answers-alphabetical.txt");      // Get vector
    random_device rd;                   // Get random seed from hardware?
    mt19937 gen(rd());                  // Use seed to initialize generator?
    uniform_int_distribution<> dis(0, myWords.size() - 1);  // Modulo doesn't work ig, so I use a new distribution of length myWords.size()

    Word chosenWord = myWords[dis(gen)];    // Finally, choose random word
    // cout << "Debugging Mode" << endl;
    // Word chosenWord = Word("humph");
    // cout << "Chosen word is: " << chosenWord.word << endl;

    string guess;

    cout << endl << "Give your best guess for the word:" << endl << endl;

    while (guess != chosenWord.word) {
        cin >> guess;
        if (guess == "exit") {
            return 0;
        } else if (guess == "override"){
            cout << chosenWord.word << endl << endl;
            continue;
        } else if (guess.length() != 5) {
            cout << "Your guess must be five letters long! Try again:" << endl << endl;
            continue;
        } else if (!isValidWord(guess, allWords)) {
            cout << "Your guess must be a valid word! Try again:" << endl << endl;
            continue;
        } else {
            assess(guess, chosenWord.word);
        }
    }

    cout << "You won!" << endl << endl;

    return 0;
}