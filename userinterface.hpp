#ifndef USERINTERFACE_HPP_INCLUDED
#define USERINTERFACE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>

#include "time.hpp"
#include "song.hpp"
#include "hashtable.hpp"

class UserInterface {
    HashTable<int, Song>* songsPtr;
    std::unordered_map<std::string, int> titleToId; // titleToIdMap

    void addSong();
    void findSong();
    void deleteSong();

    void showSongs();
    void deleteAllSongs();

    void load();
    void save();

    void enterToContinue();

public:
    UserInterface();
    ~UserInterface();
};

#endif // USERINTERFACE_HPP_INCLUDED
