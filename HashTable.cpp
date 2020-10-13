#include <iostream>
#include <math.h>
#include "HashTable.h"
#include <string>
using namespace std;

  HashTable::HashTable(){
    N = 10000;//default table size
    Table = new Entry<int, string>*[N] { nullptr };//creates our array of size N by default
    loadFactor = 0.5;//default load loadFactor

    n=0;
  }
  HashTable::HashTable(int nn,double loadfactor)//nn is the number of elements in the file, given to us in the project parameters
  {
    loadFactor = loadfactor;

    N = ceil(((double)nn/loadfactor));//gives us an approximate table size that will not exceed load factor. Rounding up just in case.
    bool foundPrime = false;

    while (!foundPrime)//searching for a prime number
    {
        bool isPrime = true;
        for (int i = 2;( i <= N / 2) && (isPrime); ++i)//checking if its prime
        {
            if (N% i == 0)
            {
                isPrime = false;
            }
        }
        if (isPrime)
        {
            foundPrime = true;
        }
        else 
        {
            N++;
        }
    }
    Table = new Entry<int,string>*[N]{ nullptr } ;//made all elements nullptr to make empty array indeces easier to spot
    n = 0;

  }
  HashTable::~HashTable() {
        // destroy all buckets one by one
        for (int i = 0; i < N; ++i) {
            Entry<int, string> *entry = Table[i];
            while (entry != nullptr) {
                Entry<int, string> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            Table[i] = nullptr;
        }
        // destroy the hash table
        delete [] Table;
    }
  int HashTable::hashFunction(int key)//compressing it
  {
    int a = 37;
    string s = to_string(key);
    int index = 0;
    int len = s.length();
    for(int i = 0; i < len;i++)
    {
      index += ((int)s[i]) * pow(a,len-i-1);
    }
    index = index % N;
    return index;
  }

  int HashTable::getN()
  {
      return N;
  }
  int HashTable::size()
  {
      return n;
  }

  int HashTable::numClusters() 
  {
      int curIndex = 0;
      int numClusters = 0;
      int startingPoint;
      while (Table[curIndex] != nullptr)//we find the first empty bucket in the array and start from there. This makes wraparound much easier later
      {
          curIndex++;
      }
      startingPoint = curIndex;
      curIndex++;//incremending so we dont accidentally start and end our for loop immediately
      int clusterSize = 0;
      bool clusterSizeCounting = false;
      for (curIndex; curIndex != startingPoint; curIndex = ((curIndex + 1) % N))//we start right after the loop and keep going
      {
          if (Table[curIndex] != nullptr)//if we hit a non null element then we need to start counting
          {
              clusterSizeCounting = true;
              
          }
          else
          {
              clusterSizeCounting = false;//as soon as we hit a null element we stop counting.
              if (clusterSize >= 2)//need to see how big our cluster was
              {
                  numClusters++;//increment numclusters
                  clusterSize = 0;//reset our cluster size
              }
          }
          if (clusterSizeCounting)
          {
              clusterSize++;
          }
      }
      return numClusters;


  }
  int HashTable::largestCluster()
  {
      int curIndex = 0;
      int maxClusters = 0;
      int startingPoint;
      while (Table[curIndex] != nullptr)//we find the first empty bucket in the array and start from there. This makes wraparound much easier later
      {
          curIndex++;
      }
      startingPoint = curIndex;
      curIndex++;//incremending so we dont accidentally start and end our for loop immediately
      int clusterSize = 0;
      bool clusterSizeCounting = false;
      for (curIndex; curIndex != startingPoint; curIndex = (curIndex + 1) % N)//we start right after the loop and keep going
      {
          if (Table[curIndex] != nullptr)//if we hit a non null element then we need to start counting
          {
              clusterSizeCounting = true;

          }
          else
          {
              clusterSizeCounting = false;//as soon as we hit a null element we stop counting.
              if (clusterSize >= 2)//need to see how big our cluster was
              {
                  if (maxClusters < clusterSize)
                  {
                      maxClusters = clusterSize;
                  }
                  clusterSize = 0;//reset our cluster size
              }
          }
          if (clusterSizeCounting)
          {
              clusterSize++;
          }
      }
      return maxClusters;


  }
  double HashTable::avgClusterSize()
  {
      int x = numClusters();//the average cluster size is simply the number of elements divided by the number of clusters.
      double avg = (double)((double)n / (double)x);//lotta doubles here but it pays to be sure
      return avg;
  }
 