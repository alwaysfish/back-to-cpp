#ifndef _BOARD_UPDATER_HPP_
#define _BOARD_UPDATER_HPP_

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>
#include "exchange_board.hpp"

void update_board(std::atomic<bool> &keep_running, ExchangeBoard &board);

#endif
