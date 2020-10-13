#ifndef LINEARPROBE_h
#define LINEARPROBE_h
#include <iostream>
#include "Entry.h"
#include <math.h>
#include "HashTable.h"
using namespace std;

class HashTable;
class LinearProbe : public HashTable {

public:
    LinearProbe();
    LinearProbe(int size, double LF);
    void put(int key, string value);
    void deleteRecord(int key);
    Entry<int, string>* find(int key);
    void printAll();
};

#endif