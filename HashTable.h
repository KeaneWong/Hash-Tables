#ifndef HASHTABLE_h
#define HASHTABLE_h
#include <iostream>
#include "Entry.h"
#include <math.h>
using namespace std;



    class HashTable {
    protected:
        Entry<int, string>** Table; //integer 
        int n;//number of elements
        int N;//size of table


        double loadFactor;

    public:
        HashTable();
        HashTable(int nn, double loadfactor);
        ~HashTable();
        int hashFunction(int key);
        virtual void put(int key, string value) = 0;
        virtual void deleteRecord(int key) = 0;
        virtual Entry<int, string>* find(int key) = 0;
        int getN();
        int size();
        virtual void printAll()=0;
        int largestCluster();
        double avgClusterSize();//just total number of elements divided by the number of clusters
        int numClusters();
    };
#endif