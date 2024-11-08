#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <math.h>

using namespace std;

// Function to display the menu and get user input
int menu()
{
    int userInput = 0;
    cout << "\nMenu\n"
         << "1. Deposit\n"
         << "2. Withdraw\n"
         << "3. Check Balance\n"
         << "4. View Transaction History\n"
         << "5. Calculate Interest\n"
         << "6. Exit\n";
    cout << "\nEnter your choice: ";
    cin >> userInput;

    //Handling errors
    try
    {
        if (userInput < 1 || userInput > 6)
        {
            throw out_of_range("Error: Please select a number between 1 and 6");
        }
    }
    catch (const out_of_range &e)
    {
        cerr << e.what() << '\n';
    }

    return userInput;
}

// Function to create an account
int account_creation(string &name)
{
    int initial_amount = 0;

    cout << "Welcome to Simple Banking System!" << endl;
    cout << "Enter your name to create a new account: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter initial deposit amount: ";
    cin >> initial_amount;

    while (initial_amount <= 0)
    { 
        cout << "Invalid amount. Enter a positive initial deposit amount: ";
        cin >> initial_amount;
    }
    
    cout << "Account created successfully!\n"<< endl;
    return initial_amount;
}

// Function to calculate interest
double calculate_interest(int balance, double rate)
{
    double interest = balance * (rate / 100.00);
    double interest_round = round(interest * 100) / 100;
    return interest_round;
}

// Function to display transaction history
void display_transaction_history(const vector<string> &types, const vector<int> &amounts)
{
    cout << "\nTransaction History:\n";
    if (types.empty())
    {
        cout << "No transactions available.\n";
    }
    else
    {
        for (size_t i = 0; i < types.size(); ++i)
        {
            cout << types[i] << ": $" << amounts[i] << endl;
        }
    }
}

int main()
{
    string name;
    int balance = 0;
    bool flag = true;
    vector<string> transaction_types;
    vector<int> transaction_amounts;
    double interest_rate;

    balance = account_creation(name);

    while (flag)
    {
        int userInput = menu();
        //using switch case to handle with different operations
        switch (userInput)
        {
        case 1:
        { // Deposit
            int amount;
            cout << "Enter deposit amount: ";
            cin >> amount;

            try
            {
                if (amount > 0)
                {
                    balance += amount;
                    transaction_types.push_back("Deposit");
                    transaction_amounts.push_back(amount);
                    cout << "Deposit successful! New Balance: $" << balance << endl;
                }
                else
                {
                    throw invalid_argument("Invalid amount. Deposit amount must be positive.\n");
                }
            }
            catch (const invalid_argument &e)
            {
                cerr << e.what() << '\n';
            }

            break;
        }
        case 2:
        { // Withdraw
            int amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;

            try
            {
                if (amount > 0 && amount <= balance)
                {
                    balance -= amount;
                    transaction_types.push_back("Withdraw");
                    transaction_amounts.push_back(amount);
                    cout << "Withdrawal successful! New Balance: $" << balance << endl;
                }
                else if (amount > balance)
                {
                    throw invalid_argument("Error: Insufficient funds for this withdrawal.\n");
                }
                else
                {
                    throw invalid_argument("Error: Invalid amount. Withdrawal amount must be positive.\n");
                }
            }
            catch (const invalid_argument &e)
            {
                cerr << e.what() << '\n';
            }

            break;
        }
        case 3: // Check Balance
            cout << "Current Balance: $" << balance << endl;
            break;
        case 4: // View Transaction History
            display_transaction_history(transaction_types, transaction_amounts);
            break;
        case 5:
        { // Calculate Interest
            cout << "Enter annual interest rate (in %): ";
            cin >> interest_rate;
            double interest = calculate_interest(balance, interest_rate);
            cout << "Interest earned: $" << interest << "\n";
            break;
        }
        case 6: // Exit
            cout << "\nThank you for using the Simple Banking System. Goodbye!\n";
            flag = false;
            break;
        }
    }

    return 0;
}
