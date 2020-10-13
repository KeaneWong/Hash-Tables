#include "DoubleHash.h"
#include <iostream>
#include <math.h>
using namespace std;





DoubleHash::DoubleHash() : HashTable()
{

};

DoubleHash::DoubleHash(int size, double LF) : HashTable(size, LF)
{

}
int DoubleHash::hashFunction2(int key)//algorithm based off of PrimeNumber - (key % PrimeNumber)
{
	int a = 11;
	return (a - (key % a));
};
void DoubleHash::put(int key, string value)
{
	int index = hashFunction(key);
	int origIndex = index;
	int probes = 0;//we overwrite the number of probes every time we call this. Keeping it in a variable allows us to access it any time after the function stops being executed
	Entry<int, string> *TBInserted = new Entry<int, string>(key, value);
	if (Table[index] == nullptr)
	{
		Table[index] = TBInserted;
		n++;
		cout << "Probes performed: " << probes << endl;
	}
	else
	{
		int i = 1;
		while (Table[index] != nullptr)
		{
			index = (origIndex + i*hashFunction2(key)) % N;//our second hashing function
			i++;
			probes++;
		}
		Table[index] = TBInserted;
		n++;
		cout << "Probes performed: " << probes << endl;

	}
};
Entry<int, string>* DoubleHash::find(int key)
{
	int index = hashFunction(key);
	int origIndex = index;
	Entry<int, string>* TBReturned;
	int probes = 0;
	if (Table[index] != nullptr && Table[index]->key() == key )//gotta always check if its null first
	{
		TBReturned = Table[index];
		cout << "Probes performed: " << probes << endl;
		return TBReturned;
	}
	else
	{
		int i = 1;
		Entry<int, string> * curEntry = Table[index];
		
		while ((curEntry == nullptr || curEntry->key() != key) && i <= N + 1)//function stops after we checked a number of slots equal to the number of buckets. This means we've gone through essentially all of the available slots
		{
			index = (origIndex + i * hashFunction2(key)) % N;//putting our second hash function to use
			i++;
			probes++;
			curEntry = Table[index];
		}
		if (curEntry != nullptr && curEntry->key() == key)//verifying. the function shouldve stopped at curValue.key = key
		{
			cout << "Probes performed: " << probes << endl;
			return curEntry;
		}
		else//if the keys arent the same then the function stopped because it traversed the whole list and did not find anything
		{
			cout << "Probes performed: " << probes << endl;
			cout << "Key " << key << " not found. " << endl;
			return nullptr;
		}
	}
};

void DoubleHash::deleteRecord(int key)//copying the function from find over, same reason as in the linear probe class
{
	int index = hashFunction(key);
	int origIndex = index;
	Entry<int, string>* TBDeleted;
	int probes = 0;
	if (Table[index] != nullptr && Table[index]->key() == key)
	{
		TBDeleted = Table[index];

	}
	else
	{
		int i = 1;
		Entry<int, string> * curEntry = Table[index];
		//the loop keeps going if the curent entry is a null pointer or it isnt a null pointer but they key is wrong, and we proceed until we've found the key or searched N times
		while ((curEntry == nullptr || curEntry->key() != key) && i <= (N + 1))//function stops after we checked a number of slots equal to the number of buckets. This means we've gone through essentially all of the available slots
		{
			index = (origIndex + i * hashFunction2(key)) % N;
			i++;
			probes++;
			curEntry = Table[index];
		}
		if (curEntry != nullptr && curEntry->key() == key)//verifying. the function shouldve stopped at curValue.key = key
		{
			TBDeleted = curEntry;
		}
		else//if the keys arent the same then the function stopped because it traversed the whole list and did not find anything
		{
			cout << "Key value not found" << endl;
			return;
		}
	}
	delete TBDeleted;
	n--;
	cout << "Probes performed: " << probes << endl;
	Table[index] = nullptr;
};
void DoubleHash::printAll()
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