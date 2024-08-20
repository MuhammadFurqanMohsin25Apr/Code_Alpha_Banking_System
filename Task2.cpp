#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

class Transaction
{
public:
    string date;
    string type;
    double amount;
    double balance;
};

class Account
{
public:
    int accountNumber;
    string accountType;
    double balance = 0;
    vector<Transaction> transactions;
};

class Customer
{
public:
    string name;
    string address;
    string phoneNumber;
    vector<Account> accounts;
};

class Bank
{
public:
    vector<Customer> customers;

    void createCustomer(string name, string address, string phoneNumber)
    {
        Customer customer;
        customer.name = name;
        customer.address = address;
        customer.phoneNumber = phoneNumber;
        customers.push_back(customer);
    }

    void createAccount(int customerIndex, int accountNumber, string accountType)
    {
        Account account;
        account.accountNumber = accountNumber;
        account.accountType = accountType;
        customers[customerIndex].accounts.push_back(account);
    }

    void deposit(int customerIndex, int accountIndex, double amount)
    {
        customers[customerIndex].accounts[accountIndex].balance += amount;

        Transaction transaction;
        transaction.date = getCurrentDateTime();
        transaction.type = "Deposit";
        transaction.amount = amount;
        transaction.balance = customers[customerIndex].accounts[accountIndex].balance;
        customers[customerIndex].accounts[accountIndex].transactions.push_back(transaction);
    }

    void withdraw(int customerIndex, int accountIndex, double amount)
    {
        if (customers[customerIndex].accounts[accountIndex].balance >= amount)
        {
            customers[customerIndex].accounts[accountIndex].balance -= amount;

            Transaction transaction;
            transaction.date = getCurrentDateTime();
            transaction.type = "Withdrawal";
            transaction.amount = amount;
            transaction.balance = customers[customerIndex].accounts[accountIndex].balance;
            customers[customerIndex].accounts[accountIndex].transactions.push_back(transaction);
        }
        else
        {
            cout << "Insufficient funds." << endl;
        }
    }

    void transfer(int sourceCustomerIndex, int sourceAccountIndex, int targetCustomerIndex, int targetAccountIndex, double amount)
    {
        if (customers[sourceCustomerIndex].accounts[sourceAccountIndex].balance >= amount)
        {
            customers[sourceCustomerIndex].accounts[sourceAccountIndex].balance -= amount;

            Transaction sourceTransaction;
            sourceTransaction.date = getCurrentDateTime();
            sourceTransaction.type = "Transfer Out";
            sourceTransaction.amount = amount;
            sourceTransaction.balance = customers[sourceCustomerIndex].accounts[sourceAccountIndex].balance;
            customers[sourceCustomerIndex].accounts[sourceAccountIndex].transactions.push_back(sourceTransaction);

            customers[targetCustomerIndex].accounts[targetAccountIndex].balance += amount;

            Transaction targetTransaction;
            targetTransaction.date = getCurrentDateTime();
            targetTransaction.type = "Transfer In";
            targetTransaction.amount = amount;
            targetTransaction.balance = customers[targetCustomerIndex].accounts[targetAccountIndex].balance;
            customers[targetCustomerIndex].accounts[targetAccountIndex].transactions.push_back(targetTransaction);
        }
        else
        {
            cout << "Insufficient funds." << endl;
        }
    }

    void displayAccountInfo(int customerIndex, int accountIndex)
    {
        cout << "Account Number: " << customers[customerIndex].accounts[accountIndex].accountNumber << endl;
        cout << "Account Type: " << customers[customerIndex].accounts[accountIndex].accountType << endl;
        cout << "Balance: Rs" << fixed << setprecision(2) << customers[customerIndex].accounts[accountIndex].balance << endl;
        cout << "Transactions:" << endl;
        for (const Transaction& transaction : customers[customerIndex].accounts[accountIndex].transactions)
        { cout << "Date: " << transaction.date << " | Type: " << transaction.type << " | Amount: Rs" << fixed << setprecision(2) << transaction.amount << " | Balance: Rs" << fixed << setprecision(2) << transaction.balance << endl;
        }
    }

private:
    string getCurrentDateTime()
    {
        time_t now = time(0);
        string dt = ctime(&now);
        dt.erase(dt.length() - 1); 
        return dt;
    }
};

int main()
{
    Bank bank;

    bank.createCustomer("Muhammad Furqan", "12th_street", "555-123422861");
    bank.createAccount(0, 23056, "Savings");
    bank.deposit(0, 0, 500.00);
    bank.withdraw(0, 0, 200.00);
    bank.deposit(0, 0, 100.00);

    bank.displayAccountInfo(0, 0);

    bank.createCustomer("Ali", "7th_street", "+91-262935181");
    bank.createAccount(1, 23057, "Current");

    bank.deposit(1, 0, 1000.00);
    bank.transfer(0, 0, 1, 0, 50.00); 

    bank.displayAccountInfo(0, 0);
    bank.displayAccountInfo(1, 0);

    return 0;
}





















