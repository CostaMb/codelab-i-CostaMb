#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>   // ✅ Needed for round()
using namespace std;

/* ---------------------------------------------------------
   Item class representing each product in the vending machine
---------------------------------------------------------- */
class Item {
public:
    string code;
    string name;
    string category;
    double price;
    int stock;

    Item(string c, string n, string cat, double p, int s)
        : code(c), name(n), category(cat), price(p), stock(s) {}

    bool isAvailable(int qty) {
        return stock >= qty;
    }

    void decrementStock(int qty) {
        stock -= qty;
    }
};

/* ---------------------------------------------------------
   Struct to store transaction records
---------------------------------------------------------- */
struct Transaction {
    string code;
    string name;
    int qty;
    double cost;
    double paid;
    double change;
    string timestamp;
};

/* ---------------------------------------------------------
   VendingMachine class controlling main functionality
---------------------------------------------------------- */
class VendingMachine {
private:
    vector<Item> items;
    map<string, int> indexByCode;
    vector<Transaction> history;
    double totalSales = 0.0;

public:

    VendingMachine() {
        loadItems();
    }

    /* Load default items */
    void loadItems() {
        items.push_back(Item("A1", "Coca-Cola", "Drinks", 1.20, 5));
        items.push_back(Item("A2", "Water 500ml", "Drinks", 0.80, 10));
        items.push_back(Item("B1", "KitKat", "Chocolate", 0.90, 6));
        items.push_back(Item("B2", "Digestive", "Biscuits", 0.75, 4));

        for (int i = 0; i < (int)items.size(); i++) {
            indexByCode[items[i].code] = i;
        }
    }

    /* Display the vending machine menu */
    void displayMenu() {
        cout << "\n========== VENDING MACHINE ==========\n";
        cout << left << setw(8) << "Code"
             << setw(15) << "Name"
             << setw(12) << "Price"
             << setw(8) << "Stock" << endl;
        cout << "-------------------------------------\n";

        for (auto &it : items) {
            cout << left << setw(8) << it.code
                 << setw(15) << it.name
                 << "£" << fixed << setprecision(2) << setw(10) << it.price
                 << setw(8) << it.stock << endl;
        }
        cout << "-------------------------------------\n";
    }

    bool hasCode(const string &code) {
        return indexByCode.find(code) != indexByCode.end();
    }

    Item& getItem(const string &code) {
        return items[indexByCode[code]];
    }

    /* Change calculation using greedy algorithm */
    map<double, int> calculateChange(double amount) {
        vector<double> denominations = {2.00, 1.00, 0.50, 0.20, 0.10, 0.05};
        map<double, int> change;
        double remaining = amount;

        for (double d : denominations) {
            int count = (int)(remaining / d + 1e-9);
            if (count > 0) {
                change[d] = count;
                remaining -= count * d;
                remaining = round(remaining * 100.0) / 100.0;   // ✅ works now
            }
        }
        return change;
    }

    string getTimestamp() {
        time_t now = time(0);
        char buf[80];
        strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
        return string(buf);
    }

    /* Main transaction flow */
    void processMachine() {
        bool run = true;

        while (run) {
            displayMenu();

            cout << "Enter item code (or Q to quit): ";
            string code;
            cin >> code;

            if (code == "Q" || code == "q") break;

            if (!hasCode(code)) {
                cout << "Invalid code. Try again.\n";
                continue;
            }

            Item &item = getItem(code);
            cout << "Selected: " << item.name << " (£" << item.price << ")\n";

            cout << "Enter quantity: ";
            string qtyInput;
            cin >> qtyInput;

            int qty = 1;
            try {
                qty = stoi(qtyInput);
                if (qty <= 0) qty = 1;
            } catch (...) {
                qty = 1;
            }

            if (!item.isAvailable(qty)) {
                cout << "Insufficient stock.\n";
                continue;
            }

            double totalCost = item.price * qty;
            cout << "Total Cost: £" << fixed << setprecision(2) << totalCost << endl;

            double paid = 0.0;
            while (paid + 1e-9 < totalCost) {
                cout << "Insert money (or C to cancel): ";
                string money;
                cin >> money;

                if (money == "C" || money == "c") {
                    cout << "Transaction cancelled. Refunding £" << paid << "\n\n";
                    paid = 0.0;
                    break;
                }

                try {
                    double amt = stod(money);
                    if (amt > 0) {
                        paid += amt;
                        cout << "Total inserted: £" << paid << endl;
                    } else {
                        cout << "Invalid amount.\n";
                    }
                } catch (...) {
                    cout << "Invalid amount.\n";
                }
            }

            if (paid < totalCost - 1e-9) continue;

            double changeAmount = paid - totalCost;
            auto change = calculateChange(changeAmount);

            item.decrementStock(qty);
            totalSales += totalCost;

            Transaction t;
            t.code = item.code;
            t.name = item.name;
            t.qty = qty;
            t.cost = totalCost;
            t.paid = paid;
            t.change = changeAmount;
            t.timestamp = getTimestamp();
            history.push_back(t);

            cout << "\nDispensing " << item.name << "...\n";
            cout << "Change returned: £" << changeAmount << endl;

            for (auto &p : change) {
                cout << "  " << p.second << " x £" << p.first << endl;
            }

            cout << "\nAnother purchase? (Y/N): ";
            char ans;
            cin >> ans;
            if (ans == 'N' || ans == 'n') run = false;
        }

        showSummary();
    }

    void showSummary() {
        cout << "\n========== SESSION SUMMARY ==========\n";
        cout << "Total Sales: £" << fixed << setprecision(2) << totalSales << endl;
        cout << "Transactions Completed: " << history.size() << endl;
        cout << "=====================================\n";
    }
};


/* ---------------------------------------------------------
   Main function
---------------------------------------------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    VendingMachine vm;
    vm.processMachine();

    return 0;
}
