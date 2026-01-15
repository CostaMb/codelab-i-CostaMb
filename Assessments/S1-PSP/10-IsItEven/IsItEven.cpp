#include <iostream>
#include <string>
using namespace std;

string checkEven(int number) {
    if (number % 2 == 0) {
        return "The provided number is even";
    } else {
        return "The provided number is odd";
    }
}

int main() {
    int value;
    cout << "Enter a number: ";
    cin >> value;

    string result = checkEven(value);
    cout << result << endl;

    return 0;
}
