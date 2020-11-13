#include <iostream>
#include <fstream>
#include "exchange_board.hpp"
#include "utils.hpp"

using namespace std;

// vector<vector<string>> ExchangeBoard::find_conversion_chains(const string &from, const string &to) const
// {
//     vector<vector<string>> chains;

//     if (from == to)
//         return chains;

//     auto ccy1_iter = m_board.find(from);
//     if (ccy1_iter == m_board.end())
//         return chains;

//     auto ccy2_iter = ccy1_iter->second.find(to);
//     if (ccy2_iter != ccy1_iter->second.end())
//     {
//         chains.push_back(vector<string>{from, to});
//         return chains;
//     }

//     return chains;
// }


double ExchangeBoard::convert(const string& from, const string& to, double amount)
{
    // if (from == to)
    //     return amount;

    // unordered_map<string, vector<shared_ptr<const ExchangeRate>>> chains;
    // auto i1 = m_board.find(from);

    // // Check if 'from' ccy even exists
    // if (i1 == m_board.end())
    //     return -1;
    
    // // Check if a direct conversion can be done
    // auto i2 = i1->second.find(to);

    // if (i2 != i1->second.end())
    // {
    //     cout << from << " -> " << to << endl;
    //     cout << i2->second->pair_name() << endl;
    //     cout << amount << " " << from << " -> " << i2->second->convert_from(from, amount) << " " << to << endl;

    //     return i2->second->convert_from(from, amount);
    // }
  
    // // Find all conversion chains, using 1 intermediary ccy
    // for (auto i_interm_ccy : i1->second)
    // {
    //     vector<shared_ptr<const ExchangeRate>> ch;
    //     auto iter_toccy = m_board[i_interm_ccy.first].find(to);

    //     if (iter_toccy != m_board[i_interm_ccy.first].end())
    //     {
    //         ch.push_back(i_interm_ccy.second);
    //         ch.push_back(iter_toccy->second);
            
    //         chains.insert(make_pair(i_interm_ccy.first, ch));
    //     }
    // }

    // for (auto chain : chains)
    // {
    //     auto ccy1 = chain.second[0];
    //     auto ccy2 = chain.second[1];

    //     cout << from << "->" << chain.first << "->" << to << endl;
    //     cout << ccy1->pair_name() << " " << ccy2->pair_name() << endl;
    //     cout << amount << " " << from << " -> " << 
    //         ccy2->convert_to(to, ccy1->convert_from(from, amount)) << " " << to << endl << endl;
    // }

    return 0;
}

shared_ptr<const ExchangeRate> ExchangeBoard::get_rate(const string &ccy_pair)
{
    lock_guard<mutex> lg(m_mutex);

    if (m_rates.find(ccy_pair) == m_rates.end())
        return nullptr;

    return m_rates[ccy_pair];
}

bool ExchangeBoard::load_rates(const string& fname)
{
    lock_guard<mutex> lg(m_mutex);

    ifstream file;
    string line;
    vector<string> tokens;
    shared_ptr<ExchangeRate> p_rate;

    file.open(fname);

    if ((file.rdstate() & ifstream::failbit) != 0)
        return false;   

    // Skip the heading
    getline(file, line);

    while (getline(file, line))
    {
        tokens = split(line, ',');

        auto sp = make_shared<ExchangeRate>(tokens[0], tokens[1],
            stod(tokens[2]), stod(tokens[3]), stod(tokens[4]));
        m_rates[sp->pair_name()] = sp;

        m_board[sp->base()].insert(sp->quote());
        m_board[sp->quote()].insert(sp->base());

        // m_board[sp->base()][sp->quote()] = sp;
        // m_board[sp->quote()][sp->base()] = sp;
    }

    return true;
}

void ExchangeBoard::update_rate(const string &ccy_pair, double last)
{
    lock_guard<mutex> ul(m_mutex);

    m_rates[ccy_pair]->update_all(last - m_rates[ccy_pair]->get_last());
}
