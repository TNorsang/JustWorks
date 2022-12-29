#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
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
    // Open the CSV file
    ifstream dataFile("customerData.csv");
    if (!dataFile.is_open())
    {
        cout << "Unable to open file" << endl;
        return 1;
    }

    // Read the file line by line and store transactions in a vector
    vector<Transaction> transactions;
    string line;
    while (getline(dataFile, line))
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
        try
        {
            t.amount = stoi(cells[2]);
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid amount: " << cells[2] << endl;
            continue;
        }
        transactions.push_back(t);
    }
    dataFile.close();

    // Sort the transactions by date
    sort(transactions.begin(), transactions.end(), [](Transaction a, Transaction b)
         { return a.date < b.date; });

    // Create a map to store customer data
    unordered_map<string, Customer> customers;

    // Iterate through the transactions and calculate the min, max, and ending balance for each customer
    for (Transaction t : transactions)
    {
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
            // Update the existing customer data
            Customer c = customers[t.customerID];
            if (c.monthYear != monthYear)
            {
                // If the month has changed, reset the min and max balance
                c.monthYear = monthYear;
                c.minBalance = t.amount;
                c.maxBalance = t.amount;
            }
            else
            {
                // Update the min and max balance
                c.minBalance = min(c.minBalance, t.amount);
                c.maxBalance = max(c.maxBalance, t.amount);
            }
            c.endingBalance += t.amount;
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