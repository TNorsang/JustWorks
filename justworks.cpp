#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

/*
Justworks wants to generate insight from a list of banking transactions occurring in customer accounts.
We want to generate minimum , maximum and ending balances by month for all customers.
You can assume starting balance at begining of month is 0.
You should read transaction data from csv files and produce output in the format mentioned below.
You can assume -ve number as debit and +ve number as credit

Please apply credit transactions first to calculate balance on a given day.
Please write clear instructions on how to run your program on a local machine.
Please use dataset in Data Tab to test your program. You do not need to add Column Header in output.
Please assume input file does not have header row.

Input CSV Format:
CustomerID, Date, Amount

Output Format:
CustomerID, MM/YYYY, Min Balance, Max Balance, Ending Balance
*/

// Transaction Class to use in Map.
class Transaction
{
public:
    // three variables to use for constructor
    string customerID;
    string date;
    float amount;

    // Constructor for Transaction and initilizing the values to class members.
    Transaction(string customerID, string date, float amount)
    {
        this->customerID = customerID;
        this->date = date;
        this->amount = amount;
    }
};

int main()
{
    // Map to store the datas. customerID as the Key and Transaction as Value.
    map<string, vector<Transaction>> transactions;

    // storing the file name
    string fileName;
    // asking what the file name is from user.
    cout << "What is the file name of the Customer? Make sure to clarify the path!" << endl;
    // Storing the name.
    cin >> fileName;

    // Openining the file.
    ifstream csvFile(fileName);

    // If any error occurs with opening the file, it'll print this out.
    if (csvFile.fail())
    {
        cerr << "Error opening File. File does not Exist!" << endl;
    }

    // Storing the line in var line.
    string line;

    // Clearing out the first line, the Header.
    getline(csvFile, line);
    line = "";

    // While loop to store all the datas and store it using stringstream.
    while (getline(csvFile, line))
    {
        // Initializing stringstream from the line.
        stringstream data(line);
        string value;

        // Getting the first value which is the customerID
        getline(data, value, ',');
        // String to integer
        string customerID = value;

        // Second value which is the date
        getline(data, value, ',');
        string date = value;

        // Third value which is the amount
        getline(data, value, ',');
        // String to Float
        float amount = stof(value);

        // Now adding the parsed values to the map. Using the key as customerID.
        transactions[customerID].push_back(Transaction(customerID, date, amount));
    }

    // Iterate over the transactions map
    for (map<string, vector<Transaction>>::iterator it = transactions.begin(); it != transactions.end(); it++)
    {
        // Get the customer ID and customer transactions
        string customerID = it->first;
        vector<Transaction> customerTransactions = it->second;

        map<string, float> balances;

        // Iterate over the transactions and apply them to the balances map
        for (vector<Transaction>::iterator it2 = customerTransactions.begin(); it2 != customerTransactions.end(); it2++)
        {
            Transaction transaction = *it2;
            string monthYear = transaction.date.substr(0, 7); // MM/YYYY
            balances[monthYear] += transaction.amount;
        }

        // Iterate over the balances map and output the minimum, maximum, and ending balances
        for (map<string, float>::iterator it3 = balances.begin(); it3 != balances.end(); it3++)
        {
            string monthYear = it3->first;
            float balance = it3->second;
            cout << "Customer: " << customerID << ": " << monthYear << ", ";

            // Calculate the minimum balance
            float minBalance = balance;
            for (map<string, float>::iterator it4 = balances.begin(); it4 != balances.end(); it4++)
            {
                float b = it4->second;
                if (b < minBalance)
                {
                    minBalance = b;
                }
            }
            cout << "Minimum Balance is " << minBalance << ", ";

            // Calculate the maximum balance
            float maxBalance = balance;
            for (map<string, float>::iterator it5 = balances.begin(); it5 != balances.end(); it5++)
            {
                float b = it5->second;
                if (b > maxBalance)
                {
                    maxBalance = b;
                }
            }
            cout << "Maximum Balance is " << maxBalance << ", " << endl;
            cout << "End Balance is " << balance << endl;
        }

        // // Going through the key and values in
        // for (const auto &pair : transactions)
        // {
        //     // Storing the key in customerID
        //     string customerID = pair.first;
        //     // Storing the multiple values inside map as
        //     const vector<Transaction> &values = pair.second;
        //     cout << "-------- "
        //          << "Customer : " << customerID << " --------" << endl;
        //     for (const Transaction &value : values)
        //     {
        //         cout << "(Date: " << value.date << ", Amount: $" << value.amount << ") " << endl;
        //     }
        //     cout << endl;
        // }
        csvFile.close();

        return 0;
    }
}