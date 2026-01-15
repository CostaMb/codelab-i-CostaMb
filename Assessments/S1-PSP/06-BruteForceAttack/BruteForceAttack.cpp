#include <iostream>
using namespace std;

int main() {
    const int correctPassword = 12345;
    int attempt;
    int attemptsLeft = 5;

    while (attemptsLeft > 0) {
        cout << "Enter password (" << attemptsLeft << " attempts remaining): ";
        cin >> attempt;

        if (attempt == correctPassword) {
            cout << "Welcome to the Secure Area" << endl;
            return 0;  // end program successfully
        }

        attemptsLeft--;
        cout << "Incorrect password." << endl;
    }

    // If loop finishes, all attempts are used
    cout << "Too many failed attempts. The authorities have been alerted!" << endl;

    return 0;
}
