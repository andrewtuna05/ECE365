#include "heap.h"

using namespace std;

heap::heap(int capacity):mapping(capacity*2){
    
    this->capacity = capacity;
    this->filled = 0;
    //accoutning for space 0 not used
    data.resize(capacity+1);
}

int heap::insert(const string &id, int key, void *pv){
    if(filled >= capacity){
        return 1;
    }else if (mapping.contains(id)){
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

int heap::setKey(const string &id, int newKey){
    bool b = false;
    
    node *pn = static_cast<node *>(mapping.getPointer(id, &b));
    if (!b){
        return 1; 
    }

    int pos = getPos(pn);

    int oldKey = data[pos].key;

    // early check: No need to percolate since the key hasn't changed
    if (oldKey == newKey){
        return 0;
    }
    
    data[pos].key = newKey;

    if (oldKey < newKey){
        // The new key is larger, so percolate down
        percolateDown(pos);
    }else if (oldKey > newKey){
        percolateUp(pos);
    }

    return 0;
}

int heap::deleteMin(string *pId , int *pKey, void *ppData){
    if(filled == 0){
        return 1;
    }
    
    if(pId){
        *pId = data[1].id;
    }

    if(pKey){
        *pKey = data[1].key;
    }

    if(ppData){
        *(static_cast<void **> (ppData)) = data[1].pData;
    }

    mapping.remove(data[1].id);
    data[1] = data[filled--];
    mapping.setPointer(data[1].id, &data[1].id);
    percolateDown(1);
    return 0;
}

int heap::remove(const string &id, int *pKey, void *ppData){
    bool b = false;

    //find node position and remove it from mapping
    node *pn = static_cast<node *>(mapping.getPointer(id, &b));
    if (!b){
        return 1; // given node does not exist
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

    if(pos > 1 && data[pos].key < data[pos/2].key){
        percolateUp(pos);
    }else if(checkPercDown(pos)){
        percolateDown(pos);
    }
    return 0;
}


void heap::percolateUp(int posCur){
    while(posCur > 1 && data[posCur].key < data[posCur/2].key){
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
        int rightChild = leftChild + 1;

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