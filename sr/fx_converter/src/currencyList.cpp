#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "currencyList.hpp"

using namespace std;

void Currency::setCode(const string &value) {
    code = value;
}

void Currency::setName(const string &value) {
    name = value;
}

void Currency::setNumericCode(const int value) {
    numericCode = value;
}

//Reads currency lists from a file and adds to vector
vector<Currency> readCurrenciesFromFile(const string &fileName) 
{
    
    ifstream file(fileName.c_str());
    if(!file) 
    {
        cout << "Cannot read from this file: " << fileName << endl;
    }
        
    string line;
    const char delim = ',';
    vector<Currency> currencies;

    while(getline(file,line))
    {
        istringstream ss(line);
        Currency currency;
        string currName, currCode;
        int currNum;
        //Read each line up to delimiter and add each value to a currency object
        getline(ss, currName, delim);
        currency.setName(currName);
        getline(ss, currCode, delim);
        currency.setCode(currCode);
        ss >> currNum; ss.ignore(256, delim);
        currency.setNumericCode(currNum);
        if (ss)
            //Add each currency object to the currencies vector
            
            currencies.push_back(currency); 
    }
    file.close();

    return currencies;
}
