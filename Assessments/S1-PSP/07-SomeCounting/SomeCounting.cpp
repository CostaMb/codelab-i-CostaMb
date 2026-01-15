#include <iostream>
using namespace std;

int main() {
    const int correctPassword = 12345;
    int attempt;
    int attemptsLeft = 5;

    while (attemptsLeft > 0) {
        cout << "Enter the password: ";
        cin >> attempt;

        if (attempt == correctPassword) {
            cout << "Welcome to the Secure Area" << endl;
            return 0;
        }

        attemptsLeft--;
        if (attemptsLeft > 0) {
            cout << "Incorrect password. Attempts remaining: " 
                 << attemptsLeft << endl;
        }
    }

    cout << "Too many failed attempts. The authorities have been alerted!" << endl;

    return 0;
}
