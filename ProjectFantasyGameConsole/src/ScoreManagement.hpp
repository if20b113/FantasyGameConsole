#pragma once

#include <vector>
#include <string>
#include <tuple>

namespace FantasyGameEngine
{
    bool score_system_init();
    void score_system_close();
    void update_score(const char* name, int score);
    std::vector<std::tuple<std::string, int, std::string>> get_scores();   
}
