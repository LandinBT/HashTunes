#ifndef TIME_HPP_INCLUDED
#define TIME_HPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream> // stringstream
#include <iomanip> // setfill, setw

class Time {
        unsigned short minute;
        unsigned short second;

        bool isValid(const unsigned short&, const unsigned short&) const;

        int toInt() const;

    public:
        Time();
        Time(const Time&);

        Time& operator = (const Time&);

        void setMinute(const unsigned short&);
        void setSecond(const unsigned short&);

        std::string toString() const;

        unsigned short getMinute() const;
        unsigned short getSecond() const;

        bool operator == (const Time&) const;
        bool operator != (const Time&) const;
        bool operator < (const Time&) const;
        bool operator <= (const Time&) const;
        bool operator > (const Time&) const;
        bool operator >= (const Time&) const;

        friend std::istream& operator >> (std::istream&, Time&);
        friend std::ostream& operator << (std::ostream&, const Time&);
    };

#endif // TIME_HPP_INCLUDED
