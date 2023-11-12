#ifndef HASHTABLE_HPP_INCLUDED
#define HASHTABLE_HPP_INCLUDED

/// DEFINITION
#include <iostream>
#include <string>
#include <limits> // numeric_limits
#include <sstream> // stringstream
#include <fstream>

#define SIZE 13
#define THRESHOLD 0.75

template <class K, class V>
class Cell {
        K key;
        V* dataPtr;

    public:
        class Exception : public std::exception {
            public:
                Exception(const std::string& message) : msg(message) {}
                const char* what() const noexcept override {
                    return msg.c_str();
                    }

            private:
                std::string msg;
            };

        Cell();
        Cell(const Cell&);
        Cell(const K&);
        Cell(const V&);
        Cell(const K&, const V&);

        Cell& operator = (const Cell&);
        Cell& operator = (const K&);
        Cell& operator = (const V&);

        ~Cell();

        void setKey(const K&);
        void setData(const V&);
        void setDataPtr(V*);

        K getKey() const;
        V getData() const;
        V* getDataPtr() const;

        bool operator == (const Cell&) const;
        bool operator != (const Cell&) const;
        bool operator < (const Cell&) const;
        bool operator <= (const Cell&) const;
        bool operator > (const Cell&) const;
        bool operator >= (const Cell&) const;

        /*template <class C, class D>
        friend std::istream& operator >> (std::istream&, Cell<C,D>&);

        template <class C, class D>
        friend std::ostream& operator << (std::ostream&, const Cell<C,D>&);*/
    };

template <class K, class V>
class HashTable {
        Cell<K, V>** elements;

        int tableSize;

        int hashFunction(const K&) const;

        void copyAll(const HashTable&);

        float loadFactor() const;

        void rehashing();

        bool isEmpty() const;

    public:
        class Exception : public std::exception {
            public:
                Exception(const std::string& message) : msg(message) {}
                const char* what() const noexcept override {
                    return msg.c_str();
                    }

            private:
                std::string msg;
            };

        HashTable();
        HashTable(const HashTable&);

        HashTable& operator = (const HashTable&);

        ~HashTable();

        void insertData(const K&, const V&);
        V searchData(const K&);
        void deleteData(const K&);

        int getSize() const;

        Cell<K, V>** getElements() const {
            return elements;
        }

        std::string toString() const;

        void deleteAll();

        void importFromDisk(const std::string&);
        void exportToDisk(const std::string&);
    };

/// IMPLEMENTATION

/// CELL
template <class K, class V>
Cell<K,V>::Cell() : dataPtr(nullptr) {}

template <class K, class V>
Cell<K,V>::Cell(const Cell& c) : key(c.key), dataPtr(new V(*(c.dataPtr))) {}

template <class K, class V>
Cell<K,V>::Cell(const K& k) : key(k) {}

template <class K, class V>
Cell<K,V>::Cell(const V& d) : dataPtr(new V(d)) {}

template <class K, class V>
Cell<K,V>::Cell(const K& k, const V& d) : key(k), dataPtr(d) {}

template <class K, class V>
Cell<K,V>& Cell<K,V>::operator = (const Cell& c) {
    if(this != &c) {
        key = c.key;
        delete dataPtr;
        dataPtr = new V(*(c.dataPtr));
        }

    return *this;
    }

template <class K, class V>
Cell<K,V>& Cell<K,V>::operator = (const K& k) {
    key = k;

    return *this;
    }

template <class K, class V>
Cell<K,V>& Cell<K,V>::operator = (const V& d) {
    dataPtr = d;
    }

template <class K, class V>
Cell<K,V>::~Cell() {
    delete dataPtr;
    }

template <class K, class V>
void Cell<K,V>::setKey(const K& k) {
    key = k;
    }

template <class K, class V>
void Cell<K,V>::setData(const V& d) {
    if(dataPtr == nullptr) {
        if((dataPtr = new V(d)) == nullptr) {
            throw Exception("Memoria no disponible, Cell.setData");
            }
        }
    else {
        *dataPtr = d;
        }
    }

template <class K, class V>
void Cell<K,V>::setDataPtr(V* ptr) {
    dataPtr = ptr;
    }

template <class K, class V>
K Cell<K,V>::getKey() const {
    return key;
    }

template <class K, class V>
V Cell<K,V>::getData() const {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, Cell.getData");
        }

    return *dataPtr;
    }

template <class K, class V>
V* Cell<K,V>::getDataPtr() const {
    return dataPtr;
    }

template <class K, class V>
bool Cell<K,V>::operator == (const Cell& c) const {
    return key == c.key;
    }

template <class K, class V>
bool Cell<K,V>::operator != (const Cell& c) const {
    return !(*this == c);
    }

template <class K, class V>
bool Cell<K,V>::operator < (const Cell& c) const {
    return key < c.key;
    }

template <class K, class V>
bool Cell<K,V>::operator <= (const Cell& c) const {
    return *this < c or *this == c;
    }

template <class K, class V>
bool Cell<K,V>::operator > (const Cell& c) const {
    return !(*this <= c);
    }

template <class K, class V>
bool Cell<K,V>::operator >= (const Cell& c) const {
    return !(*this < c);
    }

/*template <class C, class D>
std::istream& operator >> (std::istream& is, Cell<C,D>& c) {
    std::string str;

    getline(is, str, '*');
    c.key = stoi(str);

    is >> c.data;

    return is;
    }

template <class C, class D>
std::ostream& operator << (std::ostream& os, const Cell<C,D>& c) {
    return os << c.key << "*" << c.data;
    }*/

/// HashTable
template <class K, class V>
int HashTable<K,V>::hashFunction(const K& key) const {
    int hashCode;

    /// Generate hash code

    if constexpr(std::is_same<K, std::string>::value) {
        // if the key is a string
        int a = 33; // you can change this to 37, 39 o 41

        hashCode = 0;

        for(int i(key.size() - 1); i >= 0; --i) {
            hashCode += key[i] * pow(a, key.size() - 1 - i);
            }
        }
    else {
        // if the key is a number
        hashCode = std::numeric_limits<K>::digits;
        }

    /// Compression Function

    // Division method
    return abs(hashCode) % tableSize;

    /*
     * Multiplication, addition and division method
     * a & b must be random and positive numbers
     * int a = 5;
     * int b = 7;
     * return abs(hashCode * a + b) % tableSize;
    */
    }

template <class K, class V>
void HashTable<K,V>::copyAll(const HashTable& t) {
    /* Set the size of the current hash table to the
     * size of the input hash table
     */
    tableSize = t.tableSize;

    /* Allocate memory for the elements array
     * with the new size
     */
    elements = new Cell<K,V>*[tableSize];

    // iterate over each element in the input hash table
    for(int i(0); i < tableSize; ++i) {
        if(t.elements[i] != nullptr) {
            elements[i] = new Cell<K,V>(*t.elements[i]);
            }
        }
    }

template <class K, class V>
float HashTable<K,V>::loadFactor() const {
    // counter for the number of elements in the hash table
    int numElements = 0;

    // iterate over each element in the hash table
    for(int i(0); i < tableSize; ++i) {
        if(elements[i] != nullptr) {
            ++numElements;
            }
        }
    // return the load factor
    return static_cast<float>(numElements) / tableSize;
    }

template <class K, class V>
void HashTable<K,V>::rehashing() {
    // store the old size
    int oldSize = tableSize;

    // increase the size by a constant SIZE
    tableSize += SIZE;

    // allocate memory for a new elements array with the new size
    Cell<K,V>** auxElements = new Cell<K,V>*[tableSize];

    // iterate over each element in the old hash table
    for(int i(0); i < oldSize; ++i) {
        if(elements[i] != nullptr) {
            // compute the hash of the key of the current element
            int index = hashFunction(elements[i]->getKey());

            // find an empty cell in the new elements array
            while(auxElements[index] != nullptr) {
                index = (index + 1) % tableSize;
                }

            // move the current element to the new elements
            auxElements[index] = elements[i];
            }
        }

    // deallocate the memory of the old elements
    delete[] elements;

    // make the elements pointer point to the new elements array
    elements = auxElements;
    }

template <class K, class V>
bool HashTable<K,V>::isEmpty() const {
    for(int i(0); i < tableSize; ++i) {
        if(elements[i] != nullptr and elements[i]->getDataPtr() != nullptr) {
            return false;
            }
        }

    return true;
    }

template <class K, class V>
HashTable<K,V>::HashTable() {
    tableSize = SIZE;
    elements = new Cell<K,V>*[tableSize];

    for(int i(0); i < tableSize; ++i) {
        elements[i] = nullptr;
        }
    }

template <class K, class V>
HashTable<K,V>::HashTable(const HashTable& t) : elements(nullptr) {
    copyAll(t);
    }

template <class K, class V>
HashTable<K,V>& HashTable<K,V>::operator = (const HashTable& t) {
    if(this != &t) {
        deleteAll();
        copyAll(t);
        }

    return *this;
    }

template <class K, class V>
HashTable<K,V>::~HashTable() {
    deleteAll();
    }

template <class K, class V>
void HashTable<K,V>::insertData(const K& key, const V& value) {
    if(loadFactor() >= THRESHOLD) {
        // perform rehashing to increase the size
        rehashing();
        }

    /* Compute the hash of the key to get the index
     * where the element should be inserted
     */
    int index = hashFunction(key);

    // use linear probing to find an empty cell or a cell with the same key
    while(elements[index] != nullptr and elements[index]->getKey() != key) {
        index = (index + 1) % tableSize;
        }

    if(elements[index] == nullptr) {
        elements[index] = new Cell<K,V>();
        }

    // set the key & value of the cell
    elements[index]->setKey(key);
    elements[index]->setData(value);
    }

template <class K, class V>
V HashTable<K,V>::searchData(const K& key) {
    if(isEmpty()) {
        throw Exception("No hay elementos, tabla vacia");
        }

    int index = hashFunction(key);

    // use linear probing to find the cell with the given key
    while(elements[index] != nullptr and elements[index]->getKey() != key) {
        index = (index + 1) % tableSize;
        }

    if(elements[index] == nullptr) {
        throw Exception("No se encuentra en la tabla");
        }

    // return the data of the cell
    return elements[index]->getData();
    }

template <class K, class V>
void HashTable<K,V>::deleteData(const K& key) {
    if(isEmpty()) {
        throw Exception("No hay elementos, tabla vacia");
        }

    int index = hashFunction(key);

    while (elements[index] != nullptr and elements[index]->getKey() != key) {
        index = (index + 1) % tableSize;
        }

    if (elements[index] == nullptr) {
        throw Exception("No se encuentra en la tabla");
        }

    delete elements[index];
    elements[index] = nullptr;
    }

template <class K, class V>
int HashTable<K,V>::getSize() const {
    return tableSize;
    }

template <class K, class V>
std::string HashTable<K,V>::toString() const {
    if(isEmpty()) {
        throw Exception("No hay elementos, tabla vacia");
        }

    std::stringstream ss;

    for(int i(0); i < tableSize; ++i) {
        if(elements[i] != nullptr and elements[i]->getDataPtr() != nullptr) {
            ss << "#" << i << '\n'
               << elements[i]->getData().toString() << '\n'
               << '\n';
            }
        }

    return ss.str();
    }

template <class K, class V>
void HashTable<K,V>::deleteAll() {
    if(isEmpty()) {
        throw Exception("No hay elementos, tabla vacia");
        }

    for(int i(0); i < tableSize; ++i) {
        delete elements[i];
        elements[i] = nullptr;
        }

    delete[] elements;
    elements = nullptr;
    }

template <class K, class V>
void HashTable<K,V>::importFromDisk(const std::string& fileName) {
    std::fstream archive(fileName, std::ios_base::in);

    if(!archive.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo para lectura");
        }

    K key;
    V value;
    std::string str;

    while(std::getline(archive, str, '#')) {
        std::stringstream ss(str);

        std::getline(ss, str, '|');
        key = stoi(str);

        ss >> value;

        insertData(key, value);
        }

    archive.close();
    }

template <class K, class V>
void HashTable<K,V>::exportToDisk(const std::string& fileName) {
    std::fstream archive(fileName, std::ios_base::out);

    if(!archive.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo para escritura");
        }

    for(int i(0); i < tableSize; ++i) {
        if(elements[i] != nullptr and elements[i]->getDataPtr() != nullptr) {
            archive << elements[i]->getKey() << "|"
                    << elements[i]->getData() << "#";
            }
        }

    archive.close();
    }

#endif // HASHTABLE_HPP_INCLUDED
