#pragma once
#include "HashTable.h"
class HashTable;
class DoubleHash : public HashTable
{

public:
	DoubleHash();
	DoubleHash(int size, double LF);
	int hashFunction2(int key);
	void put(int key, string value);
	void deleteRecord(int key);
	Entry<int, string>* find(int key);

	void printAll();

};

