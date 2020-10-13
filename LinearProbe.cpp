#include <iostream>
#include "Entry.h"
#include <math.h>
#include "LinearProbe.h"
using namespace std;



LinearProbe::LinearProbe() :HashTable()
{

};

LinearProbe::LinearProbe(int size, double LF) :HashTable(size,LF)
{

};

void LinearProbe::put(int key, string value)
{
    int index = hashFunction(key);
    int probes = 0;
    while (Table[index] != nullptr)//if its not empty we increment and keep going
    {
        index = (index + 1) % N;//increments by 1 and also supports wraparound. Assumes we will eventually reach an empty bucket
        probes++;
    }
    Table[index] = new Entry<int, string>(key, value);
    n++;
    cout << "Probes performed: " << probes << endl;
};

  void LinearProbe::deleteRecord(int key)
  {
      int index = hashFunction(key);//search function is reprinted here. our find function can't return the entry AND its index without a pair and we need the index number to set the table index to nullptr
      int searches = 0;
      Entry<int, string>* curEntry = Table[index];
      int probes = 0;
      while ((curEntry==nullptr || curEntry->key() != key) && searches < (N + 1) )// checks to find our key value. if we have searched N+1 times then it for sure does not exist.
      {
          index = (index + 1) % N;
          curEntry = Table[index];
          searches++;
          probes++;
      }
      if (searches >= (N + 1))
      {
          cout << "Probes performed: " << probes << endl;
          cout << "Key not found, not deleted." << endl;
          return;//if we searched the whole list and if its not there then we return. Assumes worst case scenario and searches the entire list to find it.
      }
      else if (curEntry!=nullptr&&curEntry->key() == key)
      {
          Entry<int, string>* TBDeleted = Table[index];
          delete TBDeleted;
          n--;
          Table[index] = nullptr;
          cout << "Probes performed: " << probes << endl;
          cout << "Key " << key << " deleted successfully" << endl;
      }
      else
      {
          cout << "Entry Null, exiting" << endl;
          return;
      }
  };

  Entry<int,string> * LinearProbe::find(int key)
  {
    int index = hashFunction(key);
    int searches = 0;
    int probes = 0;
    Entry <int, string> *curEntry = Table[index];
    //if it is a nullptr keep going, if it isnt but the key isnt right, keep going.
    while((curEntry == nullptr || curEntry->key() != key) && searches<N+1)// checks to find our key value. if we have searched N times then it does not exist.
    {
      index = (index+1)%N;
      curEntry = Table[index];
      searches++;
      probes++;
    }
     if(searches >= N+1)
    {
      cout << "Probes performed: " << probes << endl;
      cout << "Element not found" << endl;
      return nullptr;//if we searched the whole list and its not there then we return. Assumes worst case scenario and searches the entire list to find it.
    }
    else
     {
      cout << "Probes performed: " << probes << endl;
      return curEntry;
    }
  };

  void LinearProbe::printAll()
  {
      Entry <int, string>* curEntry;
      for (int i = 0; i < N; i++)
      {
          if (Table[i] != nullptr)
          {
              curEntry = Table[i];
              cout << curEntry->value() << endl;
          }
      }
      cout << "Elements: " << n << endl;
      cout << "Table size: " << N << endl;
  };