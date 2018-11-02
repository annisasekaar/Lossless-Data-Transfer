#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;


void readFile(char text[], string& output[]) {
    ifstream fin;
    string line;
    fin.open(text);
    int idx = 0;
    if (fin.is_open()) {
        while(getline(fin,line)){
            output[idx] = line;
            idx++;
        }
    }
    fin.close();
}

void writeFile(char text[], string input[]) {
    ofstream result (text);
    int idx = 0;
    int size = sizeof(input)/sizeof(input[0]);
    cout<<size;
    if (result.is_open()) {
        while(idx < size){
            result <<input[idx];
            idx++;
        }
    }
    result.close();
}


int main(){
    string output[1000];
    char filein[] = "Input.txt";
    char fileout[] = "Output.txt";
    readFile(filein, output);
    writeFile(fileout, output);
    return 0;
}