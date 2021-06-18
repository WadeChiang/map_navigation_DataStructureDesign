#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>

enum course_name {
    empty, advanced_mathematics, linear_algebra, cpp, circuit_analysis, computer_network, automata,
    principles_of_computer_composition, mao_ze_dong_thought, data_structure_design
};

std::unordered_map<std::string, course_name> const course_name_map = {
    {"empty" , course_name::empty },
    {"advanced_mathematics",course_name::advanced_mathematics},
    {"linear_algebra",course_name::linear_algebra},
    {"cpp",course_name::cpp},
    {"circuit_analysis",course_name::circuit_analysis},
    {"computer_network",course_name::computer_network},
    {"automata",course_name::automata},
    {"principles_of_computer_composition",course_name::principles_of_computer_composition},
    {"mao_ze_dong_thought",course_name::mao_ze_dong_thought},
    {"data_structure_design",course_name::data_structure_design}
};

class timetable {
    friend class class_timetable;
private:
    std::map<int, std::pair<course_name, int>> whole_week;
public:
    timetable(std::string class_name);
    ~timetable() = default;
};


class class_timetable {
private:
    static std::vector<class_timetable*> v_class_timetable;

    std::string class_name;
    timetable class_schedule;

public:
    static std::vector<int> find_pos(std::string const class_name, std::string const course_name);
    static int find_pos(std::string const class_name, std::string const course_name, int which_day);
    class_timetable(std::string class_name);
    ~class_timetable();
};