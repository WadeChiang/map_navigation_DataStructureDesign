#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>

enum function_type {
    canteen, laundry, gate, office, teaching, playground, shop
};

std::unordered_map<std::string, function_type> const function_name_map = {
    {"canteen",function_type::canteen},
    {"laundry",function_type::laundry},
    {"gate",function_type::gate},
    {"office",function_type::office},
    {"teaching",function_type::teaching},
    {"playground",function_type::playground},
    {"shop",function_type::shop}
};

class functional_building {
private:
    static std::unordered_map<function_type, std::vector<int>> function_building_map;
    function_type function_name;
    std::vector<int> v_positions;
public:

    static std::vector<int> find_pos(std::string const s_func_name);
    functional_building(std::string function_name);
    ~functional_building();
};