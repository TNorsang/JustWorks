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

// Generate insight from a list of banking transactions occurring in customer's accounts.

// Creating a class for transaction that holds the three datas.

class Transaction
{
public:
    string customerID;
    string date;
    float Amount;

    // Constructor for Transaction and initilizing the values to class members.
    Transaction(string customerID, string date, float Amount)
    {
        this->customerID = customerID;
        this->date = date;
        this->Amount = Amount;
    }
};

class Customer
{
public:
    // Setting the variables for balances.
    // Starting balance is 0.
    int customerID;
    // Creating min,max,end balances with map
    map<string, int> minBalance;
    map<string, int> maxBalance;
    map<string, int> endBalance;
};

int main()
{

    map<string, vector<Transaction>> transactions;
    string fileName;
    cout << "What is the file name of the Customer? Make sure to clarify the path!" << endl;
    cin >> fileName;

    ifstream csvFile(fileName);

    if (csvFile.fail())
    {
        cerr << "Error opening File. File does not Exist!" << endl;
    }

    string line;

    // Clearing out the first line, the Header.
    getline(csvFile, line);

    line = "";

    while (getline(csvFile, line))
    {
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

        // Now adding the parsed values to the map

        transactions[customerID].push_back(Transaction(customerID, date, amount));
    }

    csvFile.close();

    for (auto it = transactions.begin(); it != transactions.end(); ++it)
    {
        cout << it->first << endl;
    }

    return 0;
}