#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Receipient {
private:
    string name;
    string password;
    int balance;

public:
    Receipient(string name, string password, int balance = 0)
        : name(name), password(password), balance(balance) {}

    string getName() const { return name; }
    string getPassword() const { return password; }
    int getBalance() const { return balance; }

    void setBalance(int b) { balance += b; }
    void withdrawBalance(int a) { balance -= a; }
};

class Bank {
private:
    vector<Receipient> store;

public:
    vector<Receipient>& getData() { return store; }

    bool userExist(const string& name) {
        for (auto& v : store)
            if (v.getName() == name) return true;
        return false;
    }

    void registerAccount(const string& name, const string& password) {
        if (userExist(name)) {
            cout << "Already Used Name, Try Again\n";
        } else {
            store.emplace_back(name, password);
            cout << "Account Created!\n";
        }
    }

    bool loginAccount(const string& name, const string& password) {
        for (const auto& v : store)
            if (v.getName() == name && v.getPassword() == password)
                return true;
        return false;
    }

    int nameIndex(const string& target) {
        for (int i = 0; i < store.size(); i++)
            if (store[i].getName() == target) return i;
        return -1;
    }

    void transferBalance(const string& sender, const string& receiver, int amount) {
        if (!userExist(sender) || !userExist(receiver)) {
            cout << "User doesn't exist.\n";
            return;
        }

        auto& senderAcc = store[nameIndex(sender)];
        auto& receiverAcc = store[nameIndex(receiver)];

        if (senderAcc.getBalance() < amount) {
            cout << "Insufficient balance.\n";
            return;
        }

        senderAcc.withdrawBalance(amount);
        receiverAcc.setBalance(amount);

        cout << "Transfer successful.\n";
    }
};

int main() {
    Bank bankObj;
    int optionFirst, optionSecond, numb;
    string name, password, receiver;

    while (true) {
        cout << "Bank Option\n[1] Login\n[2] Register\n[3] Exit\nYour option: ";
        cin >> optionFirst;
        if (optionFirst == 3) break;

        cout << "Name: ";
        cin >> name;
        cout << "Password: ";
        cin >> password;

        if (optionFirst == 1) {
            if (bankObj.loginAccount(name, password)) {
                cout << "Account logged\n";

                while (true) {
                    cout << "| Name: " << name
                         << " | Balance: "
                         << bankObj.getData()[bankObj.nameIndex(name)].getBalance()
                         << " |\n"
                         << "[1] Add Balance\n"
                         << "[2] Withdraw\n"
                         << "[3] Transfer\n"
                         << "[4] Logout\n";

                    cin >> optionSecond;

                    if (optionSecond == 1) {
                        cout << "Amount: ";
                        cin >> numb;
                        bankObj.getData()[bankObj.nameIndex(name)].setBalance(numb);
                    }
                    else if (optionSecond == 2) {
                        cout << "Amount: ";
                        cin >> numb;
                        bankObj.getData()[bankObj.nameIndex(name)].withdrawBalance(numb);
                    }
                    else if (optionSecond == 3) {
                        cout << "Receiver name: ";
                        cin >> receiver;
                        cout << "Amount: ";
                        cin >> numb;
                        bankObj.transferBalance(name, receiver, numb);
                    }
                    else {
                        break;
                    }
                }
            } else {
                cout << "Wrong password or name\n";
            }
        }
        else if (optionFirst == 2) {
            bankObj.registerAccount(name, password);
        }
    }
    return 0;
}