#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "hash.h"

using namespace std;

int initial_size = 50000; //initial size of dictionary
hashTable dict(initial_size);

//convert to lowercase
string lowercaser(const string &line){
    string lower_line = ""; 
    for (auto& x : line) { 
        lower_line += tolower(x);
    }
    return lower_line;
}

//function to createdictionary
void createDictionary(string &input_dict, hashTable &dict){
    ifstream file(input_dict);
    
    if(!file.is_open()){
        cout << "Could not open Dictionary File" << endl;
        return;
    }

    string line = "";
    while(!file.eof()){
        getline(file, line);
        if(line.empty()){
            continue;
        }
        line = lowercaser(line);
        //cout << "Inserting: " << line << endl;
        dict.insert(line);
    }
    file.close();
}

//function to spellcheck
void spellcheck(const string &in_file, const string &o_file ){
    ifstream input_file;
    input_file.open(in_file);

    ofstream out_file;
    out_file.open(o_file);

    string line = "";
    int line_num = 1;
    string word = "";

    vector<string> word_list;

    while(!input_file.eof()){
    
        getline(input_file, line);
        
        if(line.empty()){
            line_num++;
            continue;
        }

        line = lowercaser(line);

        for(int i = 0; i < line.length(); i++){

            char c = line[i]; //current character

            //word length more than 20 chars, write msg
            if(word.length() > 19){ 
                out_file << "Long word at line " << line_num << ", starts: " << word.substr(0,20) << endl;
                
                //skip over rest of chars
                while((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c == 39) || (c == 45)){
                    i++;
                    c = line[i];
                }
                word = "";
                continue;
            }
            //valid chars: lowercase or digit or apostrophe or hyphen 
            else if(( c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c == 39) || (c == 45)){
                word = word + c;
            }
            else{
                word_list.push_back(word);
                word = "";
            }   
        }
            if (!word.empty()) {
            word_list.push_back(word);
            word = "";  // Reset word after adding it
            }

        //analyze word list
        for(int i = 0; i < word_list.size(); i++){
            
            //if word is empty, ignore it
            if(word_list[i] == ""){
                continue;
            }

            //if word contains digit, ignore it
            bool has_digit = false;
            for(char c : word_list[i]){
                if(c >= 48 && c <= 57){
                    has_digit = true;
                    break;
                }
            }
            if(has_digit){
                continue;
            }

            //check if word exists in dictionary
            if(!dict.contains(word_list[i])){
                out_file << "Unknown word at line " << line_num << ": " << word_list[i] << endl;
            }
        }
        word_list.clear();
        line_num++;
    }
}


int main(){
    //load dict portion
    string filename;
    cout << "Enter name of Dictionary: "; 
    cin >> filename; 

    clock_t t1 = clock();
    createDictionary(filename, dict);
    clock_t t2 = clock();
    double load_time = ((double)(t2 - t1))/ CLOCKS_PER_SEC;
    cout << "Total Time (in seconds) to load dictionary: " << load_time << endl;

    //spellcheck portion
    string input_name;
    cout << "Enter name of input file: ";
    cin >> input_name;

    string out_name;
    cout << "Enter name of output file: ";
    cin >> out_name;

    clock_t t3 = clock();
    spellcheck(input_name, out_name);
    clock_t t4 = clock();
    double check_time = ((double)(t4 - t3))/ CLOCKS_PER_SEC;

    cout << "Total Time (in seconds) to check document: " << check_time << endl;

    return 0;
}