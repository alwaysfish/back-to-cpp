#include <iostream>
#include <fstream>
#include "exchange_board.hpp"
#include "utils.hpp"

using namespace std;


bool ExchangeBoard::convert(Conversion &conv)
{
    auto i1 = m_board.find(conv.from);

    // Check if a conversion from 'from' currency can be done
    if (i1 == m_board.end())
        return false;

    // Check if 'from' and 'to' currencies are the same
    if (conv.from == conv.to)
    {
        conv.converted_amount = conv.amount;
        conv.rate = 1.0;
        return true;
    }

    // Check if a direct conversion to 'to' currency can be done
    auto i2 = i1->second.find(conv.to);

    if (i2 != i1->second.end())
    {
        conv.converted_amount = i2->second->convert_from(conv.from, conv.amount);
        conv.rate = i2->second->get_from_quote(conv.from);
        conv.pair = i2->second->pair_name();
        return true;
    }
    
    unordered_map<string, vector<shared_ptr<const ExchangeRate>>> chains;
    
    // Find all conversion chains, using 1 intermediary ccy
    for (auto i_interm_ccy : i1->second)
    {
        vector<shared_ptr<const ExchangeRate>> ch;
        auto iter_toccy = m_board[i_interm_ccy.first].find(conv.to);

        if (iter_toccy != m_board[i_interm_ccy.first].end())
        {
            ch.push_back(i_interm_ccy.second);
            ch.push_back(iter_toccy->second);
            
            chains.insert(make_pair(i_interm_ccy.first, ch));
        }
    }

    // Check if any conversion chains were created
    if (chains.size() == 0)
        return false;

    double highest_amount = 0.0, converted_amount = 0.0;
    string cross_ccy;

    // Find the best conversion chain
    // A conversion chain is the best if it yields the highest amount of destination currency
    for (auto &chain : chains)
    {
        auto ccy1 = chain.second[0];
        auto ccy2 = chain.second[1];

        converted_amount = ccy2->convert_to(conv.to, ccy1->convert_from(conv.from, conv.amount));
        if (converted_amount > highest_amount)
        {
            highest_amount = converted_amount;
            cross_ccy = chain.first;
        }
    }

    if (cross_ccy != "")
    {
        auto ccy1 = chains[cross_ccy][0];
        auto ccy2 = chains[cross_ccy][1];

        conv.converted_amount = ccy2->convert_to(conv.to, ccy1->convert_from(conv.from, conv.amount));
        conv.rate = conv.converted_amount / conv.amount;
        conv.pair = conv.from + "/" + conv.to;
        conv.cross = true;
        conv.cross_ccy = cross_ccy;
    }

    return true;
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

        m_board[sp->base()][sp->quote()] = sp;
        m_board[sp->quote()][sp->base()] = sp;
    }

    return true;
}

void ExchangeBoard::update_rate(const string &ccy_pair, double last)
{
    lock_guard<mutex> ul(m_mutex);

    m_rates[ccy_pair]->update_all(last - m_rates[ccy_pair]->get_last());
}
