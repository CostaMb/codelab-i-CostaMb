#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    string answer;

    cout << "What is the capital of France? ";
    getline(cin, answer);

    string lowercaseAnswer = toLower(answer);

    if (lowercaseAnswer == "paris") {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong answer!" << endl;
    }

    return 0;
}
