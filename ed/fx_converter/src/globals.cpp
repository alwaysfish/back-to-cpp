#include "globals.hpp"

using namespace std;

mutex g_mutex_cout;

SharedQueue<QuoteUpdate> g_quote_updates;
