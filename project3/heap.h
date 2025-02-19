#ifndef _HEAP_H
#define _HEAP_H

#include "hash.h"
#include <string>
#include <vector>

using namespace std; 
  
class heap {

  public:

  // heap - The constructor allocates space for the nodes of the heap
  // and the mapping (hash table) based on the specified capacity
  heap(int capacity = 0);

  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)

  int insert(const string &id, int key, void *pv = nullptr);

  
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  
  int setKey(const string &id, int newkey);

  
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not nullptr), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  
  int deleteMin(string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);


  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  
  int remove(const string &id, int *pKey = nullptr, void *ppData = nullptr);

  private:

  class node{
    public: 
    string id; //id of node
    int key; //key of node
    void *pData; //ptr to data
  };

  int capacity;
  int filled;
  vector<node> data; //binary heap
  hashTable mapping; //map ids to ptr

  //percolate Up for insert
  void percolateUp(int posCur);

  //percolate down for remove
  void percolateDown(int posCur);

  //gets position of given node
  int getPos(node *pn);

  //checks if percolate down is valid
  bool checkPercDown(int pos);
};
#endif //_HEAP_H