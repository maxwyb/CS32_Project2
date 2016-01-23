//#include "Map.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert("Fred", 123));
//    assert(m.insert("Ethel", 456));
//    assert(m.size() == 2);
//    double d = 42;
//    assert(m.get("Fred", d)  &&  d == 123);
//    d = 42;
//    string s1;
//    assert(m.get(0, s1, d)  &&
//           ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
//    string s2;
//    assert(m.get(1, s2, d)  &&  s1 != s2  &&
//           ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
//

#include "Map.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
              "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
              "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
    CHECKTYPE(&Map::size,           int  (Map::*)() const);
    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
    
    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}

int main()
{}