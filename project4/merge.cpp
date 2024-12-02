#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LENGTH 1001

//Global Array
int merged_string[MAX_LENGTH][MAX_LENGTH];

string valid_merge(string &A, string &B, string &C){
    int a = A.length();
    int b = B.length();
    int c = C.length();

    //First check if merge
    if(a + b != c){
        return "*** NOT A MERGE ***";
    }

    //Initialize Array each time 
    for(int i = 0; i < MAX_LENGTH; i++){
        for(int j = 0; j < MAX_LENGTH; j++){
            merged_string[i][j] = 0;
        }
    }

    //Base Case
    merged_string[0][0] = 1;

    //Parse through strings checking if characters match
    for (int i = 0; i <= a; i++){
        for (int j = 0; j <= b; j++){
            if(merged_string[i][j] == 0){
                continue;
            }
            if(i < a && A[i] == C[i + j]){
                merged_string[i+1][j] = 1;
            }
            if(j < b && B[j] == C[i + j]){
                merged_string[i][j+1] = 1;
            }
        }   
    }

    if (merged_string[a][b] == 0){
        return "*** NOT A MERGE ***";
    }

    string merged = C;

    //If C is a valid merge- capitalize A **MAKE SURE A IS COMING FIRST**
    int i = a;
    int j = b;
    while(i > 0 || j > 0){
        //Added another condition to prioritize A
        if (i > 0 && (j == 0 || merged_string[i][j-1] == 0) && merged_string[i-1][j] && A[i-1] == C[i+j-1]){
            merged[i+j-1] = toupper(C[i+j-1]);
            i--;
        } else{
            j--;
        }
    }
    return merged;
}

int main(){

    string input_file;
    string output_file;
    
    cout << "Enter name of input file: ";
    cin >> input_file;

    ifstream input(input_file);
    if(!input){
        cerr << "ERROR: Could not open " << input_file << endl;
        return 1;
    }

    cout << "Enter name of output file: ";
    cin >> output_file;
    ofstream output(output_file);

    string A;
    string B;
    string C;

    while (getline(input, A) && getline(input, B) && getline(input, C)) {
        output << valid_merge(A, B, C) << endl;
    }

    input.close();
    output.close();

    return 0;
}