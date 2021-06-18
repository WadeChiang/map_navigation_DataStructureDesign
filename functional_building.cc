#include "functional_building.h"
using namespace std;

unordered_map<function_type, vector<int>> functional_building::function_building_map;

functional_building::functional_building(string function_name) {
    ifstream in_function;
    function_name += ".in";
    in_function.open(function_name, ios::in);
    string function;
    while (in_function >> function)
    {
        auto it = function_name_map.find(function);
        this->function_name = (*it).second;
        int pos;
        int num;
        in_function >> num;
        for (int i = 0; i < num; i++)
        {
            in_function >> pos;
            v_positions.push_back(pos);
        }
        function_building_map.insert(pair<function_type, std::vector<int>>
            (this->function_name, this->v_positions));
        v_positions.clear();
    }
}

functional_building::~functional_building() {
    auto it = function_building_map.find(this->function_name);
    if (it != function_building_map.end())
    {
        function_building_map.erase(it);
    }
}

vector<int> functional_building::find_pos(std::string const s_func_name) {
    auto it = function_name_map.find(s_func_name);
    auto at = function_building_map.find((*it).second);
    return (*at).second;
}