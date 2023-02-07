#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct Transactions
{
    string customerID;
    string date;
    int amount;
};

int main()
{
    cout << "Hello! Please type in the CSV File you would like to get data from." << endl;
    string csvFile;
    cin >> csvFile;

    ifstream fileName;
    fileName.open(csvFile);

    string line;
    vector<Transactions> transactions;
    while (fileName.good())
    {
        getline(fileName, line); // each line is stored in line
        stringstream ss(line);
        string parts;
        vector<string> cells;

        while (getline(ss, parts, ','))
        {
            cells.push_back(parts);
        }
        for (auto it : cells)
        {
            cout << it << endl;
        }
        // now i need to parse each line
    }
}