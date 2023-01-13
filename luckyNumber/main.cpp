#include <iostream>
#include <time.h>

using namespace std;

void initiateGame();


int luckyNumber = 1 + (time(0) % 100);




int main() {


    initiateGame(); //must play at least once


    while (true) {
        cout << "Do you want to play again? (y or n)" << endl;
        char input;
        cin >> input;
        if (input == 'y') {
            cout << "initializing game again" << endl;
            initiateGame();
            continue;
        } else if (input == 'n') {
            cout << "exiting game" <<endl;
            break;
        } else {
            cout << "pls only enter y or n" << endl;

        }
    }
    cout << "goodbye" << endl;




}

void initiateGame() {
    cout << "You got 1 tries to guess the number between 1 to 100" << endl;

    int tries = 1;
    int guess;
    while (tries > 0) {
        cout << "Input your guess" << endl;

        cin >> guess;
        if (guess == luckyNumber) {
            cout << "Congrats!" << endl;
            break;
        } else if (guess > luckyNumber) {
            cout << "guess is too big" << endl;
            tries --;
            continue;
        } else {
            cout << "guess is too small" << endl;
            tries--;
            continue;
        }
    }

    if (guess != luckyNumber) {
        cout << "Try again!" << endl;
        cout << endl;
    }
}

