#include "time.hpp"

bool Time::isValid(const unsigned short& m, const unsigned short& s) const {
    return m >= 0 and m < 100 and s >= 0 and s < 60;
    }

int Time::toInt() const {
    return minute*100 + second;
    }

Time::Time() : minute(0), second(0) {}

Time::Time(const Time& t) : minute(t.minute), second(t.second) {}

Time& Time::operator = (const Time& t) {
    minute = t.minute;
    second = t.second;

    return *this;
    }

void Time::setMinute(const unsigned short& m) {
    if(isValid(m, second)) {
        minute = m;
        }
    }

void Time::setSecond(const unsigned short& s) {
    if(isValid(minute, s)) {
        second = s;
        }
    }

std::string Time::toString() const {
    std::stringstream ss;

    ss << std::to_string(minute) << ":"
       << std::setfill('0') << std::setw(2) << std::to_string(second);

    return ss.str();
    }

unsigned short Time::getMinute() const {
    return minute;
    }

unsigned short Time::getSecond() const {
    return second;
    }

bool Time::operator == (const Time& t) const {
    return toInt() == t.toInt();
    }

bool Time::operator != (const Time& t) const {
    return !(*this == t);
    }

bool Time::operator < (const Time& t) const {
    return toInt() < t.toInt();
    }

bool Time::operator <= (const Time& t) const {
    return *this < t or *this == t;
    }

bool Time::operator > (const Time& t) const {
    return !(*this <= t);
    }

bool Time::operator >= (const Time& t) const {
    return !(*this < t);
    }

std::istream& operator >> (std::istream& is, Time& t) {
    std::string str;

    std::getline(is, str, ':');
    t.minute = stoi(str);

    std::getline(is, str, '*');
    t.second = stoi(str);

    return is;
    }

std::ostream& operator << (std::ostream& os, const Time& t) {
    return os << t.minute << ":" << t.second << "*";
    }
