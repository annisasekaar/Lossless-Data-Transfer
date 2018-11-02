#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;


void readFile(char text[], char output[], int &idx) {
    ifstream fin;
    string line;
    fin.open(text);
	char c;
    if (fin.is_open()) {
        while (fin.get(c)) {
            output[idx] = c;
            idx++;
        }
    }
    fin.close();
}

void writeFile(char text[], char input[], int idxMax) {
    ofstream result (text);
    int idx = 0;
    if (result.is_open()) {
        while(idx < idxMax){
            result <<input[idx];
            idx++;
        }
    }
    result.close();
}


int main(){
    char output[1000];
    char filein[] = "Input.txt";
    char fileout[] = "Output.txt";
	int idx = 0;
    readFile(filein, output, idx);
    writeFile(fileout, output, idx);
    return 0;
}
