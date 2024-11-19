#include "graph.h"
#include "heap.h"
#include <climits>

using namespace std;

graph::graph(ifstream &input){
    this->nodeTable = new hashTable (10000); //initialize new table w/ arbitrary size
    string line;
    string source;
    string dest;
    int cost;

    //add data to graph
    while(getline(input, line)){ 
        istringstream stream(line);
        stream >> source >> dest >> cost;
        this->addEdge(source, dest, cost);
    }
}

//bool for useDijkstra
bool graph::isNode(string name){
    return this->nodeTable->contains(name);
}

bool graph::createNode(string name){
    //check if node already in graph
    if(this->nodeTable->contains(name)){
        return false;
    }

    node *newNode = new node();
    newNode->name = name;

    this->nodeList.push_back(newNode);
    this->nodeTable->insert(name, newNode);

    return true;
}

void graph::addEdge(string source, string dest, int cost){
    bool known;
    edge *path = new edge();

    this->createNode(source);
    this->createNode(dest);

    node *source_node = static_cast<node *>(this->nodeTable->getPointer(source, &known));
    node *dest_node = static_cast<node *>(this->nodeTable->getPointer(dest, &known));

    path->cost = cost;
    path->dest = dest_node;
    source_node->adj.push_back(path);

}

void graph::Dijkstra(string source){
    node *current_node;
    heap bin_heap(nodeList.size());

    //Initializing all nodes
    for (auto current_node : this->nodeList) {
        current_node->dist = INT_MAX;  // Initialize distances to infinity
        current_node->prev = nullptr;      
        current_node->known = false;     // Node not yet processed
        bin_heap.insert(current_node->name, current_node->dist, current_node); // Insert into heap
    }

    node* start_node = (node*) this->nodeTable->getPointer(source);
    start_node->dist = 0;
    bin_heap.setKey(start_node->name, start_node->dist);

    while (bin_heap.deleteMin(nullptr, nullptr, &current_node) != 1) {
        current_node->known = true;

        if (current_node->dist == INT_MAX){
            continue;
        } 

        // Process all adjacent edges
        for (auto edge : current_node->adj) {
            node* adj_node = edge->dest;  
            int edge_cost = edge->cost;

            // Calculate the new distance
            int new_dist = current_node->dist + edge_cost;

            // Update the distance if a shorter path is found
            if (!adj_node->known && new_dist < adj_node->dist) {
                adj_node->dist = new_dist;
                adj_node->prev = current_node; // Set the parent
                bin_heap.setKey(adj_node->name, new_dist); // Update the heap
            }
        }
    }
}

void graph::generateGraph(ofstream &output){

    for (auto current_node : this->nodeList) {
        output << current_node->name << ": ";

        // If there's no path to the node
        if (!current_node->known || current_node->dist == INT_MAX) {
            output << "NO PATH" << endl;
            continue;
        }

        // Write the cost and initialize path string
        output << current_node->dist << " [";

        // Build path by traversing backwards through parents
        string path;
        node *path_node = current_node;

        while (path_node != nullptr) {
            if(!path.empty()){
                path.insert(0, ", ");
            }
            path.insert(0, path_node->name); // Add the source node to the path
            path_node = path_node->prev;
        }

        // Write the path to the file
        output << path << "]" << endl;
    }

    // Close the output file
    output.close();
}