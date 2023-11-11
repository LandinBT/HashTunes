#include "song.hpp"

int Song::nextId = 0;

Song::Song() {
    id = nextId++;
}

Song::Song(const Song& s) : id(s.id), title(s.title), artist(s.artist),
    duration(s.duration) {}

Song& Song::operator = (const Song& s) {
    id = s.id;
    title = s.title;
    artist = s.artist;
    duration = s.duration;

    return *this;
    }

void Song::setId(const int& i) {
    id = i;
    }

void Song::setTitle(const std::string& t) {
    title = t;
    }

void Song::setArtist(const std::string& a) {
    artist = a;
    }

void Song::setDuration(const Time& d) {
    duration = d;
    }

std::string Song::toString() const {
    return title + '\n' +
           artist + '\n' +
           duration.toString();
    }

int Song::getId() const {
    return id;
    }

std::string Song::getTitle() const {
    return title;
    }

std::string Song::getArtist() const {
    return artist;
    }

Time Song::getDuration() const {
    return duration;
    }

bool Song::operator == (const Song& s) const {
    return id == s.id;
    }

bool Song::operator != (const Song& s) const {
    return !(*this == s);
    }

bool Song::operator < (const Song& s) const {
    return id < s.id;
    }

bool Song::operator <= (const Song& s) const {
    return *this < s or *this == s;
    }

bool Song::operator > (const Song& s) const {
    return !(*this <= s);
    }

bool Song::operator >= (const Song& s) const {
    return !(*this < s);
    }

std::istream& operator >> (std::istream& is, Song& s) {
    std::string str;

    std::getline(is, str, '*');
    s.id = stoi(str);

    std::getline(is, s.title, '*');

    std::getline(is, s.artist, '*');

    is >> s.duration;

    return is;
    }

std::ostream& operator << (std::ostream& os, const Song& s) {
    return os << s.id << "*"
           << s.title << "*"
           << s.artist << "*"
           << s.duration;
    }
