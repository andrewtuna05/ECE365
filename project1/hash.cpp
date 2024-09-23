#include "hash.h"
#include <iostream>

using namespace std;

hashTable::hashTable(int size){
    filled = 0;
    capacity = getPrime(size);
    data.resize(capacity);
}

/* 
implemented linear probing 
*/
int hashTable::insert(const string &key, void *pv){
    
    //check first
    if(contains(key)){ 
        return 1; //already in table
    }
    
    if(filled > capacity/2){
        if(!rehash()){
            return 2;
        }
    }
    
    int pos = hash(key);
    int start = pos;

    while(data[pos].isOccupied && !data[pos].isDeleted){
        pos++; //linear probing
        
        if(pos >= capacity){
            pos = 0;
        }
        if(start == pos){
            return -1; //fail if loop thru entire table
        }
    }

    //new item
    data[pos].key = key; 
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].pv = pv;

    filled++;
    return 0;
}

bool hashTable::contains(const string &key){
    int pos = findPos(key);

    if(pos == -1){
        return false;
    }
    return true;
}

/* 
hash function from "Data Structures and Algorithms Analysis in C++ 4th Ed" by Mark Allen Weiss
*/
int hashTable::hash(const string &key){
    unsigned int hashVal = 0;

    for(char ch : key)
        hashVal = 37 * hashVal + ch;
    
    return hashVal % capacity;
}

int hashTable::findPos(const string &key){
    int pos = hash(key);
    int start = pos; 

    while(data[pos].isOccupied){
        if(data[pos].key == key && !data[pos].isDeleted){
            return pos;
        }
        pos++; //linear probing

        //wrap around
        if(pos >= capacity){
            pos = 0;
        }
        
        if (pos == start){
            return -1; //failure
        }
    }
    
    return -1; //failure
}

bool hashTable::rehash(){
    capacity = getPrime(capacity); //new size (at least 2x)
    vector<hashItem> old_data = data; //save old data into another vec
    try{
        data.resize(capacity);
    }
    catch(bad_alloc&){
        //could not allocate new memory
        return false;
    }

    //reinitialize newly sized vector
    for(int i = 0; i < capacity; i++){
         data[i].isOccupied = false;
         data[i].isDeleted = false;
    }

    int old_capacity = old_data.size();

    //copying old data into new vector
    for (int i = 0; i < old_capacity; i++){
        if(old_data[i].isOccupied && !old_data[i].isDeleted){
            insert(old_data[i].key, old_data[i].pv);
        }
    }
    return true;
}

unsigned int hashTable::getPrime(int size){
    //pre-set of 6 primes
    int primes[] = {50989, 105251, 219433, 450277, 900563, 1801187, 3602377};

    for(int i = 0; i < 6; i++){
        if(primes[i] > size){
            return primes[i];
        }
    }

    //return biggest prime in last case scenario
    return primes[6];
}




