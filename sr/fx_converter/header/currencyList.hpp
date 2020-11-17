/*Currency class allows for creating Currrency objects once read 
from file via currencyList.cpp */

#include <string>
#include <vector>

using namespace std;

class Currency
{
    private:
        string code; //3 char currency code e.g USD, GBP
        string name;
        int numericCode; //Unique int for each currency location

    public:
        Currency(): code{""}, name{""}, numericCode{0} {};
        Currency(const string& code, const string& name, const int numericCode);
        ~Currency() {};

        const string & getCode() const { return code; }
        const string & getName() const { return name; }
        const int getNumericCode() const { return numericCode; }
        void setCode(const string & value);
        void setName(const string & value);
        void setNumericCode(const int value);
};
        vector<Currency> readCurrenciesFromFile(const string &fileName);
