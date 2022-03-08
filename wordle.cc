#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// constants
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

int getContainIndex( const string &correctWord, char letter, bool taken[]) {
    for (int i = 0; i < correctWord.length(); ++i) {
                if (correctWord[i] == letter && !taken[i]) {
                        return i;
                }
        }
        return -1;
}


int main(int argc, char *argv[]) { 
    if ( argc != 2) {
        cout << "Incorrect number of arguments" << endl;
        return 0;
    }

    int attemptsLeft = 6;
    bool win = false;

    string correctWord = argv[1];
    int wordLen = correctWord.length();

    while (true) {

        string guess;

        cout << "Enter " << wordLen << " length word as guess: ";
        if (!(cin>>guess)) {
            break;
        }


        while (guess.length() != wordLen ) {
            cout << "Incorrect guess size, please enter guess of length " << wordLen << ": ";
            if (!(cin>>guess)) {
                if (cin.eof()) {
                break;
                }  
            }
            //cout << attemptsLeft;
        }

        // if it is the end of a file
        if (cin.eof()) {
            break;
        }


        //cout << "worked";
        --attemptsLeft;
        //cout << attemptsLeft;

        

        if ( guess == correctWord ) {
            win = true;
            for (int i = 0; i < guess.length(); ++i) {
                    cout << GREEN;
                    cout << guess[i];
                    cout << RESET;
            }
        } 
        // it is not the correct word
        else {

            // bool array, each index is a char in correctWord
            // keeps track of which char is taken
            bool taken[wordLen] = {false};

            for ( int i =0 ; i< guess.length(); ++i) {
                // find any correct guesses
                if (guess[i] == correctWord[i]) {
                    taken[i] = true;
                }
            }
            
            // start colouring
            for ( int i =0 ; i< guess.length(); ++i) {

                if (guess[i] == correctWord[i]) {
                    cout << GREEN;
                    cout << guess[i];
                    cout << RESET;
                    taken[i] = true;

                } else if (getContainIndex(correctWord,guess[i],taken) != -1) {
                    cout << YELLOW;
                    cout << guess[i];
                    cout << RESET;
                    int takenidx = getContainIndex(correctWord,guess[i],taken);
                    taken[takenidx] = true;
                
                } else {
                    cout << guess[i];
                }

            }

        }

        cout << endl;
        if (attemptsLeft <= 0 || win) {
            break;
        }

    }

    if (win) {
        cout << "Congrats you found the word!" << endl;
        } else if (attemptsLeft <= 0) {
                cout << "Out of guesses! The word was: " << correctWord << endl;
        }
    // if it is the end of a file
    if (cin.eof()) {
        cout << "Out of guesses! The word was: " << correctWord << endl; 
    }
    return 0;
}
