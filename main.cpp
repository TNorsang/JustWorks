// Including all the necessary modules
#include <iostream> // cout/cin etc
#include <fstream>  // input/output file
#include <string>   // string module
#include <map>      // map module
#include <sstream>  // store/parsing strings
#include <vector>   // vector module

using namespace std; // taking out std::

/*
Creating a "Struct" rather than a "Class"
Struct makes everything public by default and Class the opposite
*/
// Transaction for each customer
struct Transaction
{
    string customerID; // The key
    string date;
    int amount;
};
// Holding different customers
struct Customer
{
    // The outputs
    string customerID; // The key
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

    // Vector of objects called transaction which will store the ID, Date, Amount
    vector<Transaction> transactions;
    string line; // storing the line

    // Read the file line by line and store transactions in a vector
    while (getline(csvFile, line)) // reads till the end of line is reached
    {
        stringstream lineStream(line); // reads the values in line as if it is an input
        string cell;                   // Store each values till each comma
        vector<string> cells;          // Storing all the values in cell as a vector of strings
        // Split the line by the comma delimiter
        while (getline(lineStream, cell, ','))
        {
            cells.push_back(cell); // pushing the string in vector
        }
        // Adding all values in vector to the object t from Transaction Struct
        Transaction t;           // Transaction object
        t.customerID = cells[0]; // storing customerID from cells[0]
        t.date = cells[1];       // storing date from cells[1]

        // t.amount/stoi sometime throws an error of "Invalid_argument".
        // So I put a try catch phrase for that reason.
        try
        {
            t.amount = stoi(cells[2]); // storing amount from cells[2]
        }
        catch (invalid_argument &e)
        {
            cout << "Error Caught. Invalid Amount: " << cells[2] << endl;
            continue;
        }
        // The object is now pushed to the transactions vector
        transactions.push_back(t);
    }

    csvFile.close(); // closing the file

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