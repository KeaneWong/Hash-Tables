#include <iostream>
#include <math.h>
#include "ChainHashing.h"
using namespace std;

ChainHashing::ChainHashing() : HashTable()
{
    //default constructor, just calls HashTable
};

ChainHashing::ChainHashing(int size, double LF) : HashTable(size, LF)
{

};

void ChainHashing::put(int key, string value)
  {
    int index = hashFunction(key);
    int probes = 0 ;
    if(Table[index] == nullptr)//checking if the index points to a nullptr value. if it does that index is free
    {
    Entry<int,string> *newEntry = new Entry<int,string>(key,value);//adding a new string
    Table[index] = newEntry;
    n++;
    }
    else//means there was already an element here
    {

      Entry<int,string> *curEntry = Table[index];
      
      while(curEntry->getNext() != nullptr && curEntry->key() != key)//brings our curEntry to equal the last entry in the linked list or finds any entry with the key
      {
          
        curEntry = curEntry->getNext();
        probes++;
      }
      if(curEntry->key() == key)//replaces the value of a given element if the keys are same
      {
        curEntry->setValue(value);
      }
      else if(curEntry->getNext() ==nullptr)//if the current entry is the last entry on the chain, append our new edition to the end. 
      {
      Entry<int, string> *newEntry = new Entry<int,string>(key,value);
      newEntry->setPrev(curEntry);
      curEntry->setNext(newEntry);
      n++;
      }
    }
    cout << "Probes performed: " << probes << endl;
  }
  void ChainHashing::deleteRecord(int key)
  {
    Entry<int, string> * TBDeleted = find(key);
    int probes = 0;
    int index = hashFunction(key);
    if (TBDeleted == nullptr)//checking if we found it.
    {

      return; //do nothing
    }
    else
    {
        if (Table[index]->key() == TBDeleted->key())//checks if the found element is the first in the chain
        {

            if (TBDeleted->getNext() != nullptr)//if it has anything after it we have to reaccount for it
            {
             Table[index] = TBDeleted->getNext();//moves the chain up
             Table[index]->setPrev(nullptr);
            }
            else//if it had nothing after it we set its index to nullptr
            {
             Table[index] = nullptr;//set that index to null if the entry had nothing after it
            }
            cout << "Successfully Deleted" << endl;
      delete TBDeleted;
      n--;
      }
      else if(TBDeleted->getNext() == nullptr)//checks if its the last in its chain
      {
        Entry <int, string>* previousEntry = TBDeleted->getPrev();
        previousEntry->setNext(nullptr);//setting it to nullptr since it is now the last in the chain
        cout << "Successfully Deleted" << endl;
        delete TBDeleted;
        n--;
      }
      else//if the program got to here it means the entry it found has something before and after it
      {
          Entry <int, string>* nexEntry = TBDeleted->getNext();//setting next and previous elements equal 
          Entry<int, string>* preEntry = TBDeleted->getPrev();
          preEntry->setNext(nexEntry);
          nexEntry->setPrev(preEntry);
          cout << "Successfully Deleted" << endl;
          delete TBDeleted;
          n--;
      }
    }
  }
  Entry<int, string>* ChainHashing::find(int key)
  {
      int index = hashFunction(key);
      int probes = 0;
      if (Table[index] == nullptr)
      {
          cout << "Probes performed: " << probes << endl;
          return nullptr;//return nothing if our expression is empty
      }
      else
      {
          Entry<int, string>* curEntry = Table[index];

          while (curEntry->key() != key && curEntry->getNext() != nullptr)
          {
              curEntry = curEntry->getNext();//going down chain
              probes++;
          }
          cout << "Probes performed: " << probes << endl;
          if (curEntry != nullptr && curEntry->key() == key)
          {
              return curEntry;
          }
          else
          {
              cout << "Entry not found " << endl;
              return nullptr;
          }
      }
  };

  void ChainHashing::printAll()//traverse the list and print bucket chains sequentially
  {
      Entry <int, string> *curEntry;
      for (int i = 0; i < N; i++)
      {
          if (Table[i] != nullptr)
          {
              curEntry = Table[i];// sets/resets our curEntry to a node on the table, not in a node in a bucket on the table
              cout << curEntry->value() << endl;
                  while (curEntry->getNext() != nullptr)//causes thing to increment until we hit the last entry in the bucket
                  {
                      curEntry = curEntry->getNext();
                      cout << curEntry->value() << endl;
                  }
          }
      }
      cout << "Elements: " << n << endl;
      cout << "Table size: " << N << endl;
  }