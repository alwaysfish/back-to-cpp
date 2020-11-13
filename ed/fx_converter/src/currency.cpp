#include "currency.hpp"

Currency::Currency(const string& name, const string& code, const int numeric_code)
{
    m_name = name;
    m_code = code;
    m_numeric_code = numeric_code;
}
