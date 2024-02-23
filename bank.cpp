#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Account {
private:
    string name;
    long accountNumber;
    double balance;
    double interestRate;

public:
    Account(string name, long accountNumber, double balance, double interestRate = 0.0)
        : name(name), accountNumber(accountNumber), balance(balance), interestRate(interestRate) {}

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn " << amount << " successfully.\n";
        } else {
            cout << "Insufficient balance.\n";
        }
    }

    void calculateInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest calculated and added to the account.\n";
    }

    void display() {
        cout << "Account Holder: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }

    double getBalance() const {
        return balance;
    }

    long getAccountNumber() const {
        return accountNumber;
    }
};

class Bank {
private:
    vector<Account> accounts;
    const string filename = "accounts.txt";

public:
    Bank() {
        loadAccountsFromFile();
    }

    ~Bank() {
        saveAccountsToFile();
    }

    void loadAccountsFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string name;
            long accountNumber;
            double balance, interestRate;

            while (file >> name >> accountNumber >> balance >> interestRate) {
                Account account(name, accountNumber, balance, interestRate);
                accounts.push_back(account);
            }

            file.close();
            cout << "Accounts loaded successfully.\n";
        }
    }

    void saveAccountsToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const Account &account : accounts) {
                file << account.getAccountNumber() << " " << account.getBalance() << endl;
            }

            file.close();
            cout << "Accounts saved successfully.\n";
        }
    }

    void createAccount() {
        string name;
        long accountNumber;
        double balance, interestRate;

        cout << "Enter account holder's name: ";
        cin >> name;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter initial balance: ";
        cin >> balance;
        cout << "Enter interest rate (%): ";
        cin >> interestRate;

        Account newAccount(name, accountNumber, balance, interestRate);
        accounts.push_back(newAccount);
        cout << "Account created successfully.\n";
    }

    void deposit(long accountNumber, double amount) {
        for (Account &account : accounts) {
            if (accountNumber == account.getAccountNumber()) {
                account.deposit(amount);
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void withdraw(long accountNumber, double amount) {
        for (Account &account : accounts) {
            if (accountNumber == account.getAccountNumber()) {
                account.withdraw(amount);
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void calculateInterest(long accountNumber) {
        for (Account &account : accounts) {
            if (accountNumber == account.getAccountNumber()) {
                account.calculateInterest();
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void display(long accountNumber) {
        for (Account &account : accounts) {
            if (accountNumber == account.getAccountNumber()) {
                account.display();
                return;
            }
        }
        cout << "Account not found.\n";
    }
};

int main() {
    Bank bank;
    int choice;
    long accountNumber;
    double amount;

    do {
        cout << "\nBank Management System Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Calculate Interest\n";
        cout << "5. Display Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                bank.deposit(accountNumber, amount);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                bank.withdraw(accountNumber, amount);
                break;
            case 4:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.calculateInterest(accountNumber);
                break;
            case 5:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.display(accountNumber);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
