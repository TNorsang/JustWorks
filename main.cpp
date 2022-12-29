#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Transaction
{
    string customerID;
    string date;
    int amount;
};

struct Customer
{
    string customerID;
    string monthYear;
    int minBalance;
    int maxBalance;
    int endingBalance;
};

int main()
{
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

    // Read the file line by line and store transactions in a vector
    // All the datas inside the vector are objects. so {Transaction 1,}
    vector<Transaction> transactions;
    string line;
    while (getline(csvFile, line))
    {
        // Split the line by the comma delimiter
        stringstream lineStream(line);
        string cell;
        vector<string> cells;
        while (getline(lineStream, cell, ','))
        {
            cells.push_back(cell);
        }
        // Add the transaction to the vector
        Transaction t;
        t.customerID = cells[0];
        t.date = cells[1];

        // This sometime throws an error of "Invalid_argument". So I put a try catch phrase for that reason.
        t.amount = stoi(cells[2]);
        try
        {
            t.amount = stoi(cells[2]);
        }
        catch (invalid_argument &e)
        {
            cout << "Error Caught. Invalid Amount: " << cells[2] << endl;
            continue;
        }

        transactions.push_back(t);
    }
    csvFile.close();

    // Sort the transactions by date
    sort(transactions.begin(), transactions.end(), [](Transaction a, Transaction b)
         { return a.date < b.date; });

    // Create a map to store customer data
    map<string, Customer> customers;

    // Iterate through the transactions and calculate the min, max, and ending balance for each customer
    for (Transaction t : transactions)
    {
        // This captures the first two characters of the date and last four characters.
        string monthYear = t.date.substr(0, 2) + '/' + t.date.substr(6, 4);
        if (customers.count(t.customerID) == 0)
        {
            // Create a new customer if they don't exist in the map
            Customer c;
            c.customerID = t.customerID;
            c.monthYear = monthYear;
            c.minBalance = t.amount;
            c.maxBalance = t.amount;
            c.endingBalance = t.amount;
            customers[t.customerID] = c;
        }
        else
        {
            // [10,10,5,-50,-50,30]
            // currentMin = 10
            // Update the existing customer data
            Customer c = customers[t.customerID];
            c.endingBalance += t.amount;

            if (c.endingBalance < c.minBalance)
            {
                c.minBalance = c.endingBalance;
            }
            if (c.endingBalance > c.maxBalance)
            {
                c.maxBalance = c.endingBalance;
            }
            customers[t.customerID] = c;
        }
    }

    // Print the results
    for (auto pair : customers)
    {
        Customer c = pair.second;
        cout << c.customerID << ", " << c.monthYear << ", " << c.minBalance << ", " << c.maxBalance << ", " << c.endingBalance << endl;
    }

    return 0;
}