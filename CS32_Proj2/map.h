#ifndef map_h
#define map_h

#include <iostream>
#include <string>
using namespace std;

typedef std::string KeyType;
typedef double ValueType;

class Map
{
public:
    Map();
    ~Map();
    Map(const Map& anotherMap);
    Map& operator=(const Map& anotherMap);
    
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);

private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        Node* previous;
    };
    Node* head;
    Node* tail;
    int nItems;
};

bool combine(const Map& m1, const Map& m2, Map& result);

void subtract(const Map& m1, const Map& m2, Map& result);

#endif /* map_h */
