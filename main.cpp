#include <iostream>
#include "DoubleHash.h"
#include "ChainHashing.h"
#include "LinearProbe.h"
#include "HashTable.h"
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

int main() {
    
    string filename; 
    cout << "Hello, welcome to the FBI HOME LOCATIONAL WATCHLIST SYSTEM. Please enter the file name of the data base to be processed: " << endl;
    cin >> filename;
    ifstream FBIwatchlist;
    FBIwatchlist.open(filename);
    
    if (!FBIwatchlist) //exiting if it doesnt work
    {
        cout << "INVALID FILE NAME TERMINATING IMMEDIATELY";
        exit(1); // terminate with error
    }
    

    int numElements = 0;
    FBIwatchlist >> numElements;

    double lf;
    cout << "Enter the desired load factor: " << endl;
    std::cin >> lf;
    cout << "Select a mode of processing: " << endl;
    cout << "1. Linear Probing " << endl;
    cout << "2. Chain Hashing " << endl;
    cout << "3. Double Hashing " << endl;
    int choice;
    std::cin.ignore();
    std::cin.clear();
    std::cin >> choice;
    
    HashTable  * myTable;
    switch (choice)
    {
    case 1:
        myTable = new LinearProbe(numElements, lf);
        break;

    case 2:
        myTable = new ChainHashing(numElements, lf);
        break;

    case 3:
        myTable = new DoubleHash(numElements, lf);
        break;
    default:
        myTable = new LinearProbe(numElements,lf);//just in case an incorrect option is selected
        break;
    }
    string entry;
    std::cin.ignore();
    std::cin.clear();
    FBIwatchlist.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (getline(FBIwatchlist,entry))
    {


        int j = 0;
        string key1;
        //cout << "Entry is " << entry << endl;
        while (entry[j] != ',')
        {
            key1 = key1 + entry[j];
            j++;
        }
        int key2 = stoi(key1);
        //cout << "key2 is: " << key2 << endl;
        myTable->put(key2, entry);
   }

    
    do
    {
        cout << "Enter an option:" << endl;
        cout << "1. Search for a record" << endl;
        cout << "2. Insert a record" << endl;
        cout << "3. Delete a record" << endl;
        cout << "4. List all records" << endl;
        cout << "5. Exit" << endl<<endl;
       int input;
       cin >> input;


        switch (input)
        {
        case 1:
        {
            Entry<int, string>* searched;
            int k;
            cout << "Enter a key to search for: " << endl;
            cin >> k;

            searched = myTable->find(k);
            if (searched == NULL)
            {
                cout << "Entry not found" << endl;
            }
            else
            {
                cout << "Entry is " << searched->value()<<endl;
            }
        }
            break;
        
        case 2: 
        {
            string s;
            cout << "Enter a county/state code, a population, and a county name all separated by commas: " << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin,s);
            //cin.clear();
            //cin.ignore();
           // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            int j = 0;
            string key1;
            cout << "Entry is " << s << endl;
          while (s[j] != ',')
            {
                key1 = key1 + s[j];
                j++;
            }
            int key2 = stoi(key1);
            cout << "key2 is: " << key2 << endl;
            myTable->put(key2, s); 

        }
            break;

        case 3:
        {
           cout<< "Enter the key of the node to be deleted" << endl;
           int TBDel;
           cin >> TBDel;
           myTable->deleteRecord(TBDel);

        }
            break;

        case 4:
        {
            myTable->printAll();

        }
            break;

        case 5: 
        {
            exit(0);
        }
            break;

        case 6:
        {
            cout << "Ultra secret debug menu: " << endl;
            cout << "The number of clusters:" << myTable->numClusters() << endl;
            cout << "The average cluster size: " << myTable->avgClusterSize() << endl;
            cout << "The size of the largest cluster is: " << myTable->largestCluster() << endl;
        }
            break; 
        default: 
            cout << "Incorrect input try again" << endl;
            break;


        }
        cin.ignore();
        cin.clear();
    } while (true);
}