#ifndef assembler
#define assembler

#include <bits/stdc++.h>
using namespace std;

#define MAXS 1024
#define MAXW 10

int ERROR_FLAG = 0; // error flag
int PROGADDR;       // store program address
int CSADDR;         // store control section address
int CSLTH;          // store control section length
int EXECADDR;       // store execution address 

map<string, int> ESTAB;     // data structure to store external symbols

// struct to store a text record
struct textrec {
    int firstaddr;
    string record;
};

string inputFile = "input.txt";
string outputFile = "loaderOutput.txt";
string estabfile = "estab.txt";

// Utility functions
int getProgramAddress();
int search_textrec(vector<textrec> textrecords, int num_addr);

// Funtions for pass 1 and 2
int pass_one(ifstream &fin);
int pass_two(ifstream &fin, ofstream &fout);

#endif
