#include <iostream>
#include <string>
#include "map.h"

using namespace std;

Map::Map() {
    head = nullptr;
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
        nItems = 0;
    }
}

Map::Map(const Map& anotherMap) {
    if (anotherMap.nItems == 0) {
        nItems = 0;
        head = nullptr;
    } else {
        KeyType key;
        ValueType value;
        for (int i = 0; i < anotherMap.nItems; i++) {
            anotherMap.get(i, key, value);
            insert(key, value);
        }
    }
}

Map& Map::operator=(const Map& anotherMap) {
    if (&anotherMap == this)
        return (*this);
    
    if (nItems > 0) {
        Node* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            delete ptr->previous;
        }
        delete ptr;
        
        head = nullptr;
        nItems = 0;
    }
    
    if (anotherMap.nItems > 0) {
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
    if (nItems == 0) {
        head = new Node;
        
        head->key = key;
        head->value = value;
        head->next = nullptr;
        head->previous = nullptr;
    } else {
        Node* ptr = head;
        if (ptr->key == key)
            return false;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            if (ptr->key == key)
                return false;
        }
        
        ptr->next = new Node;
        ptr->next->key = key;
        ptr->next->value = value;
        ptr->next->next = nullptr;
        ptr->next->previous = ptr;
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
        if (head->key == key) {
            if (ptr->next != nullptr) {
                head = ptr-> next;
                ptr->next->previous = nullptr;
                delete ptr;
                nItems--;
                return true;
            } else {
                head = nullptr;
                delete ptr;
                nItems--;
                return true;
            }
        }
        
        while (ptr->next != nullptr) {
            ptr = ptr->next;
            
            if (ptr->key == key) {
                if (ptr->next != nullptr) {
                    ptr->previous->next = ptr->next;
                    ptr->next->previous =ptr->previous;
                    delete ptr;
                    nItems--;
                    return true;
                } else {
                    ptr->previous->next = nullptr;
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
    int count = 0;
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
    Node* temp;
    temp = other.head;
    other.head = head;
    head = temp;
    
    int tempNItems;
    tempNItems = other.nItems;
    other.nItems = nItems;
    nItems = tempNItems;
}


bool combine(const Map& m1, const Map& m2, Map& result) {
    result = *new Map;
    
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
        
        result.insertOrUpdate(key, value);
    }
    
    for (int i = 0; i < m2.size(); i++) {
        KeyType key;
        ValueType value;
        m2.get(i, key, value);
        
        if (!m1.contains(key))
            result.insertOrUpdate(key, value);
    }
    
    if (hasConflict)
        return false;
    else
        return true;
}


void subtract(const Map& m1, const Map& m2, Map& result) {
    result = *new Map;
    
    for (int i = 0; i < m1.size(); i++) {
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        
        if (!m2.contains(key))
            result.insertOrUpdate(key, value);
    }
}
