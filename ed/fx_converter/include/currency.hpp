#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <string>

using namespace std;

class Currency
{
private:
    string m_name;
    string m_code;
    int m_numeric_code;

public:
    Currency(const string& name, const string& code, const int numeric_code);
    ~Currency() {}

    const string& name() const { return m_name; }
    const string& code() const { return m_code; }
    int numeric_code() const { return m_numeric_code; }
};

#endif