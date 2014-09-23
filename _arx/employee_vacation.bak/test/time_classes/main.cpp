#include <iostream>
#include <sstream>

#include <unistd.h>

#include "datetime.h"

using namespace std;

int main()
{
    rele_auto::datetime tm = rele_auto::datetime::current();
    std::stringstream os;
    os << "date : " << tm.day() << "-" << tm.month() << "-" << tm.year() << std::endl;
    os << "time : " << tm.hour() << ":" << tm.minute() << ":"
       << tm.second() << "." << tm.millisecond() << std::endl;
    std::cout << os.str( ) << std::endl;
    os.seekp(0);
    os.clear();

    std::cout << "sleeping ..." << std::endl;
    sleep(5);

    rele_auto::datetime tm1 = rele_auto::datetime::current();
    os << "old time" << std::endl;
    os << "time : " << tm.hour() << ":" << tm.minute() << ":"
       << tm.second() << "." << tm.millisecond() << std::endl;
    os << "new time" << std::endl;
    os << "time : " << tm1.hour() << ":" << tm1.minute() << ":"
       << tm1.second() << "." << tm1.millisecond() << std::endl;


    std::cout << os.str( );

    return 0;
}

