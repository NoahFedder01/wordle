#include "word.h"
#include <fstream>
#include <cmath>
#include <sstream>
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
initializeWithRatings does exactly what it sounds like
*/
// vector<Word> initializeWithRatings() {
//     ifstream file("words-with-ratings.txt");     // Open file
//     if (!file) {                                 // Handle errors opening file
//         cerr << "Error opening file" << endl;
//     }
//     string line, word;                // Parsing variable
//     vector<Word> words;         // Prepare vector to be filled
//     Word temp;
//     while (getline(file,line)) {    // Parse txt

//         stringstream ss(line);
//         ss >> temp.rating;
//         ss >> temp.word;
//         words.push_back(temp);    // Create Word object for each word, push to back of vector
//     }
//     return words;
// }
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
bool isValidWord(string guess, vector<Word>& myWords) {
    for (int i = 0; i < myWords.size(); i++) {
        if (guess == myWords[i].word) {
            return true;
        }
    }
    return false;
}

/*
incrementBaseThree
*/
void incrementBaseThree(vector<int>& input) {   // ChatGPT magic
    for (int i = 4; i >= 0; i--) {
        if (++input[i] < 3) return;
        input[i] = 0;
    }
}

/*
Does it work:
determines if a word can work with the given set of restrictions

I think there are no errors here, but it has not been tested very extensively
*/
bool doesItWork(Word guess, Word real, char params[5]) {
    int mapping[5][5] = {       // 5x5 mapping of guess to answer
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    for (int i = 0; i < 5; i++) {           // if guess[i] == answer[j], 0 becomes 1, if i == j too, 0 becomes 2
        for (int j = 0; j < 5; j++) {
            if (guess.word[i] == real.word[j]) {
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
    char ret[5];

    for (int i = 0; i < 5; i++) {
        placehold = 'N';
        for (int j = 0; j < 5; j++) {
            if (mapping[i][j] == 1 && placehold != 'G') {
                placehold = 'Y';
            } else if (mapping[i][j] == 2) {
                placehold = 'G';
            }
        }
        ret[i] = placehold;
    }

    for (int i = 0; i < 5; i++) {
        if (ret[i] != params[i]) {
            return false;
        }
    }

    return true;
}

/*
average returns the average value of a set of doubles.
*/
double average(vector<double> data) {
    double sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum / data.size();
}

/*
Bit algorithm: brute force calculate FOR EVERY WORD how many 
other words would be cut out of the pool if
(ex for crane):
crane
N N N N N
or
crane
Y N N N N
or
crane
Y N Y G Y

were the result of the guess (125 possibilities per word)

UNDER CONSTRUCTION

The result of this function is that words
*/
void giveWordRating(Word& word, vector<Word>& small) {
    char params[5];             // For parameters to be passed to doesItWork
    double denom, length = small.size();
    double placehold;
    vector<double> ratings;     // Stores all possible ratings
    vector<int> myVec(5,0);     // For incrementing to all 243 parameter possibilities
    for (int j = 0; j < 243; j++) {      // Check against every possibility
        placehold = 0;
        for (int k = 0; k < 5; k++) {           // Load parameter array using the incrementing vector
                if (myVec[k] == 0) {
                    params[k] = 'N';
                } else if (myVec[k] == 1) {
                    params[k] = 'Y';
                } else {
                    params[k] = 'G';
                }
            }
        for (int i = 0; i < length; i++) {             // Check every word
            if (doesItWork(small[i], word, params)) {
                placehold++;
            }
        }

        denom = placehold;
        denom /= length;                // gives proportion of words that work with this word and the parameters
        for (int i = 0; i < placehold; i++) {       // and then essentially multiplies it by the number of times it worked (to weight it)
            ratings.push_back(denom);   // The above is questionably true at best. This function returns higher values
        }   // if a given word has the 14855 total possibilites spread out the most along the 243 different possible parameters
        incrementBaseThree(myVec);     // resulting in the lowest median value here being rated the best
    }           // This function is confusing but I think it is the best possible rating function (only in terms of results)
//                                                      Basically, this is black magic
    word.rating = log2(1/(average(ratings)));  // then average all proportions and their probabilities, and rate using log2
    return;
}

/*
Call giveWordRating for every word
*/
void populateRatingAndFile(vector<Word>& myWords, vector<Word>& small) {
    Word& best = myWords[0];
    ofstream outputFile("running-words.txt");
    for (int i = 0; i < myWords.size(); i++) {
        Word& temp = myWords[i];
        giveWordRating(temp, small);
        // cout << temp.word << " " << temp.rating << endl;
        cout << i + 1 << " of " << myWords.size() << " words rated." << endl;
        if (temp.rating > best.rating) {
            best = temp;
            cout << "New best word: " << best.word << " with a score of " << best.rating << endl;
        }
        if (outputFile.is_open()) {
            outputFile << temp.word << "," << temp.rating << endl;
        }
    }
    // cout << "Final best word: " << best.word << " with a score of " << best.rating << endl;
    return;
}

void populateRating(vector<Word>& myWords, vector<Word>& small) {
    for (int i = 0; i < myWords.size(); i++) {
        giveWordRating(myWords[i], small);
        cout << i + 1 << " of " << myWords.size() << " words rated." << endl;
    }
    // cout << "Final best word: " << best.word << " with a score of " << best.rating << endl;
    return;
}

/*
purge
gets rid of any words in a vector that do not match
a given set of parameters for a given word
*/
void purge(vector<Word>& vec, Word guess, char params[5]) {
    for (int i = 0; i < vec.size(); i++) {
        if (!doesItWork(guess, vec[i], params)) {
            vec.erase(vec.begin() + i);
            i--;
        }
    }
}

void crappySort(vector<Word> vec) {
    ofstream outputFile("rated-and-sorted.txt");
    while (vec.size() != 0) {
        int temp = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].rating > vec[temp].rating) {
                temp = i;
            }
        }
        if (outputFile.is_open()) {
            outputFile << vec[temp].word << "," << vec[temp].rating << endl;
            cout << vec[temp].word << " added to output file." << endl;
        }
        vec.erase(vec.begin() + temp);
    }
}

vector<Word> lessCrappySort(vector<Word> vec) {
    vector<Word> newVec;
    while (vec.size() != 0) {
        int temp = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].rating > vec[temp].rating) {
                temp = i;
            }
        }

        newVec.push_back(vec[temp]);

        vec.erase(vec.begin() + temp);
    }
    return newVec;
}

int main() {
    vector<Word> myWords = initializeWithRatings("efficientSorted.txt");      // Get vector
    vector<Word> small = init("wordle-answers-alphabetical.txt");
    vector<Word> reference = myWords;
    int timer = 0, max = 5;
    string name;
    char check = 'n';
    char params[5];
    string param;
    Word temp;

    cout << endl << "Exit the program any time by typing the word 'exit'" << endl;

    while (timer < 6) {

        if (timer >= 2) {       // Toggle from elimination mode to solve mode on move 3
            for (int i = 0; i < myWords.size(); i++) {
                for (int j = 0; j < small.size(); j++) {
                    if (myWords[i].word == small[j].word) {
                        small[j].rating = myWords[i].rating;
                    }
                }
            }

            myWords = small;
        }

        timer++;

        if (small.size() < max) {
            max = small.size();
        }
        if (max < 0) {
            max = 1;
        }

        if (timer > 1) {
            populateRating(myWords, small);
        }

        myWords = lessCrappySort(myWords);

        cout << endl << "The top words and their scores are:" << endl;
        for (int i = 0; i < max; i++) {
            cout << myWords[i].word << " " << myWords[i].rating << endl;     // add rating to output of top nuumbers here if needed
        }

        cout << endl;
        check = 'n';
        while (check != 'y') {          // Recieve word used
            cout << "What word did you use (enter in lowercase)?:" << endl << endl;
            cin >> name;
            if (name == "exit") {
                return 0;
            }
            if (!isValidWord(name, reference)) {
                cout << "You must enter a valid five letter word from the list." << endl << endl;
                continue;
            }
            while (0 == 0) {
                cout << endl << name << " was your choice? (y/n)" << endl << endl;
                cin >> check;
                cout << endl;
                if (check != 'y' && check != 'n') {
                    cout << "Your choice must be either 'y' or 'n'." << endl << endl;
                    continue;
                } else {
                    break;
                }
            }
        }
        check = 'n';
        while (check != 'y') {          // Recieve parameters
            cout << "What was the result? (use G for green, Y for yellow, N for grey)" << endl;
            cout << "For example: GNNYN" << endl << endl;
            cin >> param;
            if (param == "exit") {
                return 0;
            }
            if (param.size() != 5) {
                cout << "Please enter a five letter combination in the example format." << endl;
                continue;
            }
            if (param[0] != 'G' && param[0] != 'Y' && param[0] != 'N') {
                cout << "Parameters must be G, Y, or N." << endl;
                continue;
            }
            if (param[1] != 'G' && param[1] != 'Y' && param[1] != 'N') {
                cout << "Parameters must be G, Y, or N." << endl;
                continue;
            }
            if (param[2] != 'G' && param[2] != 'Y' && param[2] != 'N') {
                cout << "Parameters must be G, Y, or N." << endl;
                continue;
            }
            if (param[3] != 'G' && param[3] != 'Y' && param[3] != 'N') {
                cout << "Parameters must be G, Y, or N." << endl;
                continue;
            }
            if (param[4] != 'G' && param[4] != 'Y' && param[4] != 'N') {
                cout << "Parameters must be G, Y, or N." << endl;
                continue;
            }
            while (0 == 0) {
                cout << endl << param << " was the result? (y/n)" << endl << endl;
                cin >> check;
                cout << endl;
                if (check != 'y' && check != 'n') {
                    cout << "Please enter either 'y' or 'n'." << endl;
                    continue;
                } else {
                    break;
                }
            }
            if (param == "GGGGG") {
                cout << "Wordle Completed" << endl;
                return 0;
            }
        }

        for (int i = 0; i < 5; i++) {
            params[i] = param[i];
        }

        temp = Word(name);

        purge(small, temp, params);

        if (small.size() == 1) {
            cout << endl << "The answer is " << small[0].word << endl << endl;
            return 0;
        }

    }

    cout << "Out of turns :(" << endl << endl;

    return 0;
}