#include "log.h"
#include <fstream>
#include <ctime>
using namespace std;
void lprint(std::string info){
    ofstream of;
    string date;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    date=std::to_string(1900 + ltm->tm_year)+"-"+std::to_string( 1 + ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday)+".log";
    of.open(date,ios::out|ios::app);
    of<<info<<endl;
}
