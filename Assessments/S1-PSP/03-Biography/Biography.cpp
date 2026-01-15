#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    string hometown;
    int age;

    // Input for name (supports first+last name)
    cout << "Enter your name: ";
    getline(cin, name);

    // Input for hometown (supports multi-word towns)
    cout << "Enter your hometown: ";
    getline(cin, hometown);

    // Input for age with validation
    cout << "Enter your age: ";
    while (!(cin >> age)) {
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // discard invalid input
        cout << "Invalid age. Please enter a number: ";
    }

    // Final output using ONE cout
    cout << name << "\n" << hometown << "\n" << age << endl;

    return 0;
}
