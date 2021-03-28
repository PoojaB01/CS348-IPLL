#ifndef pascal
#define pascal

#include <bits/stdc++.h>
using namespace std;
#include "180101057_hash_table.cpp"

#define MAX_SIZE 256
#define MAXLEN 100

// used to check if token is first word in a line
int new_line = 1;

// indicates current line number
int line_no = 1;

// print output line corresponding to each token
void printCode(int token_code, string token_spec = "");

// insert symbol in hash table
int install_id(string id);

// insert number in hash table
int install_num(string number);

// specify name of output files
string outputFile = "lex_output.txt";
string id_table_file = "id_table.txt";
string int_table_file = "int_table.txt";

// pointer to output file
ofstream fout;

// data structure to store ids
hash_table id_table(MAX_SIZE);

// data structure to store ints
hash_table int_table(MAX_SIZE);

#endif
