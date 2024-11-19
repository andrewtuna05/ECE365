#include "graph.h"

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string valid_start(graph &g){
    string start_node;

    while (true) {
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> start_node;

        if (g.isNode(start_node)) {  // Check if the node exists
            return start_node;
        }
        cin.clear();
    }
}

int main(){
    string graph_file;
    string output_file;

    // Prompt the user for the graph file
    cout << "Enter name of input file: ";
    cin >> graph_file;

    // Open the graph file and initialize the graph
    ifstream input_file(graph_file);
    if (!input_file) {
        cerr << "ERROR: Could not open " << graph_file << endl;
        return 1;
    }
    graph g(input_file);

    // Prompt the user for a valid starting vertex
    string start_node = valid_start(g);

    // Measure the time taken to apply Dijkstra's algorithm
    clock_t start_time = clock();
    g.Dijkstra(start_node);
    clock_t end_time = clock();
    double dijkstra_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << dijkstra_time << endl;

    // Prompt the user for the output file name
    cout << "Enter name of output file: ";
    cin >> output_file;

    // Write the results to the output file
    ofstream output(output_file);
    if (!output) {
        cerr << "ERROR: Could not open file " << output_file << " for writing." << endl;
        return 1;
    }
    g.generateGraph(output); // Generate output in the required format
    output.close();

    return 0;
}
