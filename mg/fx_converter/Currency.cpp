#include "Currency.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

bool getFileContent(string fileName)
{
    // Open the File
    ifstream file(fileName.c_str());
    // Check if object is valid
    if(!file)
    {
        std::cout << "Cannot open the File : "<<fileName<<endl;
        return false;
    }
    string str;
    string element;
    vector<string> outside;
    // Read the next line from File untill it reaches the end.
    
    string line;
    const char delim = ',';
    while(getline(file,line))
    {
        istringstream ss(line);
        Currency currency;
        ss.read((char*)&currency, sizeof(currency));
        
        for (int i = 0; i < 4; i++){
            getline(ss, line, ',');
            if (i=0){
                currency.setName(line);
            }
            else if(i=1){
               
                currency.setCode(line);
            }
            else if(i=2){ 
                currency.setNumericCode(stoi(line));
            }
            else if(i=3){ 
                currency.setNumericCode(stoi(line));
            }
        //if (ss)
            //vec.push_back(currency);
    }
    
    }  
    //Close The File
    file.close();
    return true;
    
}