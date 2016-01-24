#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

//void test_string_to_double() {
//    Map m;
//    assert(m.empty() == true); // test empty()
//    m.insert("Ethan", 12.1); // test insert()
//    m.insert("Jackie", 8.8);
//    assert(m.size() == 2); // test size()
//    assert(m.insert("Jackie", 11.1) == false && m.update("Jeremy", 19.8) == false); // cannot insert or update
//    m.update("Ethan", 9.2); // test update()
//    m.insertOrUpdate("Gopi", 2); // should insert
//    m.insertOrUpdate("Jackie", 20.13); // should update
//    assert(m.erase("Gopi") == true && m.erase("Max") == false); // test erase()
//    assert(m.contains("Jeremy") == false); // test contains()
//    
//    string key;
//    double value;
//    m.get("Ethan", value); // test the first get()
//    assert(value == 9.2);
//    m.get(0, key, value); // test the second get()
//    assert(key == "Ethan" && value == 9.2);
//    m.get(1, key, value);
//    assert(key == "Jackie" && value == 20.13);
//    
//    Map n;
//    n.insert("Angry bird", 100);
//    m.swap(n); // test swap()
//    assert(m.contains("Angry bird") == true && n.contains("Ethan") == true && m.size() == 1 && n.size() == 2);
//}

//void test_int_to_string() {
//    Map m;
//    assert(m.empty() == true); // test empty()
//    m.insert(12, "Ethan"); // test insert()
//    m.insert(8, "Jackie");
//    assert(m.size() == 2); // test size()
//    assert(m.insert(8, "Dick") == false && m.update(19, "Jeremy") == false); // cannot insert or update
//    m.update(12, "Colin"); // test update()
//    m.insertOrUpdate(2, "Gopi"); // should insert
//    m.insertOrUpdate(8, "bird"); // should update
//    assert(m.erase(2) == true && m.erase(100) == false); // test erase()
//    assert(m.contains(101) == false && m.contains(2) == false && m.contains(12) == true); // test contains()
//    
//    int key;
//    string value;
//    m.get(12, value); // test the first get()
//    assert(value == "Colin");
//    m.get(0, key, value); // test the second get()
//    assert(key == 12 && value == "Colin");
//    m.get(1, key, value);
//    assert(key == 8 && value == "bird");
//    
//    Map n;
//    n.insert(100, "Angry bird");
//    m.swap(n); // test swap()
//    assert(m.contains(100) == true && n.contains(8) == true && m.size() == 1 && n.size() == 2);
//}

//void test()
//{
//    Map m;
//    assert(m.insert(123, "Fred"));
//    assert(m.insert(456, "Ethel"));
//    assert(m.size() == 2);
//    string s;
//    assert(m.get(123, s)  &&  s == "Fred");
//    s = "";
//    int i1;
//    assert(m.get(0, i1, s)  &&
//           ((i1 == 123  &&  s == "Fred")  ||  (i1 == 456  &&  s == "Ethel")));
//    int i2;
//    assert(m.get(1, i2, s)  &&  i1 != i2  &&
//           ((i2 == 123  &&  s == "Fred")  ||  (i2 == 456  &&  s == "Ethel")));
//}

void test()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    double d = 42;
    assert(m.get("Fred", d)  &&  d == 123);
    d = 42;
    string s1;
    assert(m.get(0, s1, d)  &&
           ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
    string s2;
    assert(m.get(1, s2, d)  &&  s1 != s2  &&
           ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
}

//#include "Map.h"
//#include <type_traits>
//
//#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
//
//static_assert(std::is_default_constructible<Map>::value,
//              "Map must be default-constructible.");
//static_assert(std::is_copy_constructible<Map>::value,
//              "Map must be copy-constructible.");
//
//void ThisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
//    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
//    CHECKTYPE(&Map::size,           int  (Map::*)() const);
//    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
//    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
//    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
//    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
//    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
//    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
//    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
//    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
//    
//    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
//    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
//}
//
//int main()
//{}

int main()
{
    //test_int_to_string();
    //test_string_to_double();
    test();
    cout << "Passed all tests" << endl;
}
