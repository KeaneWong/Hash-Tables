#ifndef CHAINHASHING_h
#define CHAINHASHING_h
#include <iostream>
#include <math.h>
#include "HashTable.h"
using namespace std;

class HashTable;
class ChainHashing : public HashTable 
{
  
  protected:

  public: 
     ChainHashing();
  ChainHashing(int size, double LF );
  void put(int key, string value);
  void deleteRecord(int key);
  Entry<int,string> * find(int key);
  void printAll();
};
#endif