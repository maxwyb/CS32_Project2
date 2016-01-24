#include <iostream>
#include "map.h"

using namespace std;

Map::Map() {
    head = nullptr;
    tail = nullptr;
    nItems = 0;
}

Map::~Map() {
    if (nItems > 0) {
        Node* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            delete ptr->previous;
        }
        delete ptr;
        
        head = nullptr;
        tail = nullptr;
        nItems = 0;
    }
}

Map::Map(const Map& anotherMap) {
    head = nullptr; // first construct an empty "Map"
    tail = nullptr;
    nItems = 0;
    
    if (anotherMap.nItems > 0) {
        KeyType key;
        ValueType value;
        for (int i = 0; i < anotherMap.nItems; i++) {
            anotherMap.get(i, key, value);
            insert(key, value);
        }
    }
}

Map& Map::operator=(const Map& anotherMap) {
    if (&anotherMap == this) // if the two variables point to the same "Map"
        return (*this);
    
    if (nItems > 0) { // first empty the "Map"
        Node* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            delete ptr->previous;
        }
        delete ptr;
        
        head = nullptr;
        tail = nullptr;
        nItems = 0;
    }
    
    if (anotherMap.nItems > 0) { // construct the "Map" to be equal to "anotherMap"
        KeyType key;
        ValueType value;
        for (int i = 0; i < anotherMap.nItems; i++) {
            anotherMap.get(i, key, value);
            insert(key, value);
        }
    }
    
    return (*this);
}

bool Map::empty() const {
    return (head == nullptr);
}

int Map::size() const {
    return nItems;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    if (nItems == 0) { // the "Map" is empty before insertion
        head = new Node;
        tail = head;
        
        head->key = key;
        head->value = value;
        head->next = nullptr;
        head->previous = nullptr;
    } else {
        Node* ptr = head;
        if (ptr->key == key)
            return false;
        while (ptr->next != nullptr) {
            ptr = ptr->next;  // traverse to the last node in the doubly-linked list
            if (ptr->key == key)
                return false;
        }
        
        ptr->next = new Node;
        ptr->next->key = key;
        ptr->next->value = value;
        ptr->next->next = nullptr;
        ptr->next->previous = ptr;
        tail = ptr->next;
    }
    
    nItems++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    if (nItems == 0)
        return false;
    else {
        Node* ptr = head;
        if (head->key == key) {
            head->value = value;
            return true;
        }
        
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            if (ptr->key == key) {
                ptr->value = value;
                return true;
            }
        }
        return false;
    }
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (!insert(key, value))
        update(key, value);
    return true;
}

bool Map::erase(const KeyType& key) {
    if (nItems == 0)
        return false;
    else {
        Node* ptr = head;
        if (head->key == key) { // erase the first node
            if (ptr->next != nullptr) { // the "Map" has more than one node
                head = ptr->next;
                ptr->next->previous = nullptr;
                delete ptr;
                nItems--;
                return true;
            } else { // the "Map" has only one node
                head = nullptr;
                tail = nullptr;
                delete ptr;
                nItems--;
                return true;
            }
        }
        
        while (ptr->next != nullptr) { // traverse to every node
            ptr = ptr->next;
            
            if (ptr->key == key) {
                if (ptr->next != nullptr) { // the node to erase is not the last node
                    ptr->previous->next = ptr->next;
                    ptr->next->previous =ptr->previous;
                    delete ptr;
                    nItems--;
                    return true;
                } else { // the node to erase is the last node
                    ptr->previous->next = nullptr;
                    tail = ptr->previous;
                    delete ptr;
                    nItems--;
                    return true;
                }
            }
        }
        return false;
    }
}

bool Map::contains(const KeyType& key) const {
    if (nItems == 0)
        return false;
    else {
        Node* ptr = head;
        if (ptr->key == key)
            return true;
        
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            if (ptr->key == key)
                return true;
        }
        return false;
    }
}

bool Map::get(const KeyType& key, ValueType& value) const {
    if (nItems == 0)
        return false;
    else {
        Node* ptr = head;
        if (ptr->key == key) {
            value = ptr->value;
            return true;
        }
        
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            
            if (ptr->key == key) {
                value = ptr->value;
                return true;
            }
        }
        return false;
    }
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (!(i >= 0 && i < nItems))
        return false;
    
    Node* ptr = head;
    int count = 0; // count the number of the current node
    if (i == count) {
        key = ptr->key;
        value = ptr->value;
        return true;
    }
    
    while (ptr->next != nullptr) {
        ptr = ptr->next;
        count++;
        
        if (i == count) {
            key = ptr->key;
            value = ptr->value;
            return true;
        }
    }
    
    return false;
}

void Map::swap(Map& other) {
    Node* tempHead; // swap the "head" pointer
    tempHead = other.head;
    other.head = head;
    head = tempHead;
    
    Node* tempTail; // swap the "tail" pointer
    tempTail = other.tail;
    other.tail = tail;
    tail = tempTail;
    
    int tempNItems; // swap "nItems"
    tempNItems = other.nItems;
    other.nItems = nItems;
    nItems = tempNItems;
}


bool combine(const Map& m1, const Map& m2, Map& result) {
    Map combinedMap = *new Map; // create a new "Map" to store result, to avoid aliasing
    
    bool hasConflict = false;
    for (int i = 0; i < m1.size(); i++) {
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        
        if (m2.contains(key)) {
            ValueType value2;
            m2.get(key, value2);
            if (value != value2) {
                hasConflict = true;
                continue;
            }
        }
        
        combinedMap.insertOrUpdate(key, value);
    }
    
    for (int i = 0; i < m2.size(); i++) {
        KeyType key;
        ValueType value;
        m2.get(i, key, value);
        
        if (!m1.contains(key))
            combinedMap.insertOrUpdate(key, value);
    }
    
    result = combinedMap;
    
    if (hasConflict)
        return false;
    else
        return true;
}


void subtract(const Map& m1, const Map& m2, Map& result) {
    Map subtractedMap = *new Map;
    
    for (int i = 0; i < m1.size(); i++) {
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        
        if (!m2.contains(key))
            subtractedMap.insertOrUpdate(key, value);
    }
    
    result = subtractedMap;
}
