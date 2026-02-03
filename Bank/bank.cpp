#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "transaction.h"

using namespace std;

class Receipient {
private:
    string name;
    string password;
    string role;
    int balance;

public:
    Receipient(string name, string password, int balance = 0, string role = "user")
        : name(name), password(password), balance(balance), role(role) {}

    string getName() const { return name; }
    string getPassword() const { return password;}
    string getRole() const { return role; }
    int getBalance() const { return balance; }
    
    void setRole(string role){this->role = role;}
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
    system("clear");
    Bank bankObj;
    int optionFirst, optionSecond, optionThird,numb;
    string name, password, receiver;
    bankObj.getData().emplace_back("Eljay", "2528", 9999999999, "admin");
    while (true) {
        cout << "Bank Option\n[1] Login\n[2] Register\n[3] Exit\nYour option: ";
        cin >> optionFirst;
        if (optionFirst == 3){
          system("clear"); break;
        }
        
        if (cin.fail()){ 
          cout << "Terminating Program Invalid Input, Input the available choice only " << endl;
          break;
        }
        
        cout << "Name: ";
        cin >> name;
        cout << "Password: ";
        cin >> password;

        if (optionFirst == 1) {
            if (bankObj.loginAccount(name, password) && bankObj.getData()[bankObj.nameIndex(name)].getRole() == "admin") {
              while(true){
                cout << "Admin Panel\n[1] Set balance\n[2] Transfer\n[3] List User\n[4] Delete User\n[5] Logout";
                cin >> optionThird;
                if(optionThird == 1){
                  while(true){
                      cout << "Set Balance\n[1] Yours\n[2] Other\n[3] Exit\nOption: " <<endl;
                      string receiver; int option,amount;
                      cin >> option;
                      if(option == 3){system("clear"); break;}
                      cout << "Amount: "; cin >> amount;
                      if(option == 1){
                        bankObj.getData()[bankObj.nameIndex(name)].setBalance(amount);
                        cout << "Amount Set!" << endl;
                      }else if(option == 2){
                        cout << "Receiver Name: ";
                        cin >> receiver;
                        bankObj.getData()[bankObj.nameIndex(receiver)].setBalance(amount);
                        cout << "Amount Set!" << endl;; 
                      }
                  }
                }else if(optionThird == 2){
                  cout << "Transfer balance" << endl;
                  cout<< "Receiver Name: "; cin >> receiver;
                  cout << "Amount: "; cin >> numb;
                  bankObj.transferBalance(name, receiver, numb);
                }else if(optionThird == 3){
                  int ind = 0;
                  for(const auto v : bankObj.getData()){
                    cout << "[" << ind << "]" << "   " << v.getName() << "   " << v.getPassword() << "   " << v.getBalance() << "   " << v.getRole() << endl;
                    ind++;
                  }
                }else if(optionThird == 4){
                  int ind;
                  cout << "Delete User through Index. | User List To Find Index. |" << endl;
                  cout << "Index: "; cin >> ind;
                  bankObj.getData().erase(bankObj.getData().begin() + ind);
                  cout << "successfully Deleted User!" <<endl;
                }else{
                  system("clear");
                  break;
                }
              }
            }else if(bankObj.loginAccount(name, password)){
                cout << "Account logged\n";

                while (true) {
                    cout << "| Name: " << name
                         << " | Balance: "
                         << bankObj.getData()[bankObj.nameIndex(name)].getBalance() <<"|\n[1] Add Balance\n[2] Withdraw\n[3] Transfer\n[4] Logout\n";
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
                        system("clear");
                        break;
                    }
                }
            } else {
                cout << "Wrong password or name\n";
            }
        }else if (optionFirst == 2) {
            bankObj.registerAccount(name, password);
        }
    }
    return 0;
}