#include "heap.h"
#include "hash.h"

using namespace std;

heap::heap(int capacity):mapping(capacity*2){
    
    this->capacity = capacity;
    this->filled = 0;
    
    //accoutning for space 0 not used
    data.resize(capacity+1);
}

int heap::insert(const string &id, int key, void *pv){
    
    //if heap is full
    if(filled >= capacity){
        return 1;
    //if node w/ id exists already, return error
    }else if (mapping.contains(id)){
        return 2;
    }
    //creat/insert data at end
    filled++;
    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;
    
    //update hash table for new node
    mapping.insert(id, &data[filled]);

    //percolate up to maintain heap order
    percolateUp(filled);
    return 0;
}

int heap::setKey(const string &id, int newKey){
    bool b = false;
    
    node *pn = static_cast<node *>(mapping.getPointer(id, &b));
    //check if id exists-- return error if not
    if (!b){
        return 1; 
    }

    int pos = getPos(pn);

    //save oldKey 
    int oldKey = data[pos].key;

    // early check: No need to percolate since the key hasn't changed
    if (oldKey == newKey){
        return 0;
    }
    
    //set node to newKey
    data[pos].key = newKey;

    //percolating depending on inequality
    if (oldKey < newKey){
        percolateDown(pos);

    }else if (oldKey > newKey){
        percolateUp(pos);
    }

    return 0;
}

int heap::deleteMin(string *pId , int *pKey, void *ppData){
    
    //check if heap empty
    if(filled == 0){
        return 1;
    }
    
    //If pId, pKey, ppdData are provided, preserve it
    if(pId){
        *pId = data[1].id;
    }

    if(pKey){
        *pKey = data[1].key;
    }

    if(ppData){
        *(static_cast<void **> (ppData)) = data[1].pData;
    }

    //remove id of Min element
    mapping.remove(data[1].id);

    //update hashtable and restore heap order
    data[1] = data[filled--];
    mapping.setPointer(data[1].id, &data[1].id);
    
    //restore heap order
    percolateDown(1);
    return 0;
}

int heap::remove(const string &id, int *pKey, void *ppData){
    bool b = false;

    //check if id exists-- return error if not
    node *pn = static_cast<node *>(mapping.getPointer(id, &b));
    if (!b){
        return 1;
    }
    
    int pos = getPos(pn);

    if (pKey) {
        *pKey = data[pos].key;
    }

    if (ppData) {
        *(static_cast<void **>(ppData)) = data[pos].pData;
    }
    mapping.remove(id);

    data[pos] = data[filled--];
    mapping.setPointer(data[pos].id, &data[pos]);

    //restore heap order
    if(pos > 1 && data[pos].key < data[pos/2].key){
        percolateUp(pos);
    }else if(checkPercDown(pos)){
        percolateDown(pos);
    }
    return 0;
}


void heap::percolateUp(int posCur){
    //continue percolating up until heap order is restored 
    while(posCur > 1 && data[posCur].key < data[posCur/2].key){
        //swap via heap order property
        swap(data[posCur], data[posCur/2]);
        //update hash table
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[posCur/2].id, &data[posCur/2]);
        posCur = posCur/2;
    }
}

void heap::percolateDown(int posCur){
    //continue percolating down until heap order is restored
    while(posCur <= filled/2){
        int minChild = posCur;
        int leftChild = 2 * posCur;
        int rightChild = leftChild + 1;

        //check if left child exists and is smaller than current
        if (leftChild <= filled && data[leftChild].key < data[minChild].key) {
            minChild = leftChild;
        }

        //check if right child exists and is smaller than current
        if(rightChild <= filled && data[rightChild].key < data[minChild].key){
            minChild = rightChild;
        }

        //if heap order satisfied-- stop
        if (minChild == posCur){
            break;
        }

        //swap to restore heap order
        swap(data[posCur], data[minChild]);

        //update hash table
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[minChild].id, &data[minChild]);
        posCur = minChild;
    }
}


int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}

//check for percdown to simplify conditional
bool heap::checkPercDown(int pos){
    
    int leftChild = 2*pos; 
    int rightChild = leftChild + 1; 

    //check left
    if(leftChild <= filled && data[leftChild].key < data[pos].key){
        return true;
    //check right 
    }else if(rightChild <= filled && data[rightChild].key < data[pos].key){
        return true;
    }

    //percDown not needed
    return false;
}