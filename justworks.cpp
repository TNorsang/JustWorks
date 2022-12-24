#include <iostream>
#include <string>
#include <fstream>

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

class Customer
{
public:
    // Setting the variables for balances.
    // Starting balance is 0.
    string name;
    double min = 0;
    double max;
    double endBalance;

    Customer(string name)
    {
        this->name = name;
    }
};

int main()
{
    string fileName;
    cout << "What is the file name of the Customer?" << endl;
    cin >> fileName;

    ifstream csvFile(fileName);

    if (csvFile.fail())
    {
        cerr << "Error opening File" << endl;
        return 1;
    }

    string line;
}