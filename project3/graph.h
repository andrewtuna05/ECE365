#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class graph {
    
    public:
    
    //constructor to load initial graph
    graph(ifstream &input);

    //check if node exists in graph
    bool isNode(string name);

    //Runs algorithm on graph
    void Dijkstra(string source);

    void generateGraph(ofstream &output);

    private:
        bool createNode(string name);

        void addEdge(string source, string dest, int cost);

        class edge; //forward declaration
        class node{
            public:
                string name;
                list <edge *> adj;
                node *prev;
                bool known; //is the best path known from source to this node
                int dist; //cost of best path
        };

        class edge{
            public:
            int cost; //cost of the edge
            node *dest;
        };
        
        //List of nodes in graph
        list<node *> nodeList;
        //Hash table for Nodes
        hashTable *nodeTable;

};
#endif //_GRAPH_H