#include "heap.h"

using namespace std;

heap::heap(int capacity):mapping(capacity*2){
    
    this->capacity = capacity;
    this->filled = 0;
    //accoutning for space 0 not used
    data.resize(capacity+1);
    mapping = hashTable(capacity*2); //why is this used?
}

int heap::insert(const string &id, int key, void *pv){
    if(filled >= capacity){
        return 1;
    }else if (mapping.contains[id]){
        return 2;
    }
    filled++;
    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;
    mapping.insert(id, &data[filled]);

    percolateUp(filled);
    return 0;
}


int heap::setKey(const string &id, int key);




int heap::deleteMin(string *pId , int *pKey, void *ppData);




int heap::remove(const string &id, int *pKey, void *ppData);





void heap::percolateUp(int posCur){
    while(posCur > 1 && data[posCur].key < data[posKey/2].key){
        swap(data[posCur], data[posCur/2]);
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[posCur/2].id, &data[posCur/2]);
        posCur = posCur/2;
    }
}

void heap::percolateDown(int posCur){
    while(posCur <= filled/2){
        int minChild = posCur;
        int leftChild = 2 * posCur;
        int rightChild = 2 * posCur + 1;

        if (leftChild <= filled && data[leftChild].key < data[minChild].key) {
            minChild = leftChild;
        }

        if(rightChild <= filled && data[rightChild].key < data[minChild].key){
            minChild = rightChild;
        }

        if (minChild == posCur){
            break;
        }

        swap(data[posCur], data[minChild]);
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[minChild].id, &data[minChild]);
        posCur = minChild;
    }
}

int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}