#include "timetable.h"

using namespace std;

const int MAX_LESSON_NUM = 11;

timetable::timetable(string class_name) {
    ifstream in_table;
    class_name += ".in";
    in_table.open(class_name, ios::in);
    int serial, location;
    string name;
    in_table >> serial >> name >> location;
    for (size_t i = 1; i <= 5 * MAX_LESSON_NUM; i++)
    {
        if (serial == i)
        {
            auto it = course_name_map.find(name);
            auto e_course_name = (*it).second;
            whole_week.insert(map<int, pair<course_name, int>>::value_type(i,
                pair<course_name, int>(e_course_name, location)));
            in_table >> serial >> name >> location;
        }
        else
        {
            whole_week.insert(map<int, pair<course_name, int>>::value_type(i,
                pair<course_name, int>(course_name::empty, 0)));
        }
    }
}

vector<class_timetable*> class_timetable::v_class_timetable;

vector<int> class_timetable::find_pos(std::string const class_name, std::string const course_name) {
    auto timetable_it = v_class_timetable.begin();
    while ((*timetable_it)->class_name != class_name)
    {
        ++timetable_it;
    }

    auto course_it = course_name_map.find(course_name);
    auto e_course_name = (*course_it).second;

    vector<int> pos;
    for (size_t i = 0; i < 5 * MAX_LESSON_NUM; i++)
    {
        auto it = (*timetable_it)->class_schedule.whole_week[i];
        if (it.first == e_course_name)
        {
            if (find(pos.begin(), pos.end(), it.second) == pos.end())
                pos.push_back(it.second);
        }
    }
    return pos;
}


int class_timetable::find_pos(std::string const class_name, std::string const course_name, int which_day) {
    auto timetable_it = v_class_timetable.begin();
    while ((*timetable_it)->class_name != class_name)
    {
        ++timetable_it;
    }
    auto course_it = course_name_map.find(course_name);
    auto e_course_name = (*course_it).second;

    int pos = 0;
    for (size_t i = ((which_day - 1) * MAX_LESSON_NUM + 1); i <= which_day * MAX_LESSON_NUM; i++)
    {
        auto it = (*timetable_it)->class_schedule.whole_week[i];
        if (it.first == e_course_name)
        {
            pos = it.second;
        }
    }
    return pos;
}

class_timetable::class_timetable(std::string class_name) : class_schedule(class_name) {
    this->class_name = class_name;
    v_class_timetable.push_back(this);
}

class_timetable::~class_timetable() {
    auto it = find(v_class_timetable.begin(), v_class_timetable.end(), this);
    if (it != v_class_timetable.end())
    {
        v_class_timetable.erase(it);
    }
}