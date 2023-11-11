#ifndef SONG_HPP_INCLUDED
#define SONG_HPP_INCLUDED

#include <iostream>
#include <string>

#include "time.hpp"

class Song {
        int id;
        static int nextId;

        std::string title;
        std::string artist;
        Time duration;

    public:
        Song();
        Song(const Song&);

        Song& operator = (const Song&);

        void setId(const int&);
        void setTitle(const std::string&);
        void setArtist(const std::string&);
        void setDuration(const Time&);

        std::string toString() const;

        int getId() const;
        std::string getTitle() const;
        std::string getArtist() const;
        Time getDuration() const;

        bool operator == (const Song&) const;
        bool operator != (const Song&) const;
        bool operator < (const Song&) const;
        bool operator <= (const Song&) const;
        bool operator > (const Song&) const;
        bool operator >= (const Song&) const;

        friend std::istream& operator >> (std::istream&, Song&);
        friend std::ostream& operator << (std::ostream&, const Song&);
    };

#endif // SONG_HPP_INCLUDED
