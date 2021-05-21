#ifndef pascal
#define pascal

#include <bits/stdc++.h>
using namespace std;
#include "hash_table.cpp"

#define MAX_SIZE 256
#define MAXLEN 1024

// Check for errors
int ERROR_FLAG = 0;

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
// string outputFile = "lex_output.txt";
string id_table_file = "id_table.txt";
// string int_table_file = "int_table.txt";

// pointer to output file
ofstream fout;

// data structure to store ids
hash_table id_table(MAX_SIZE);

// data structure to store ints
hash_table int_table(MAX_SIZE);



// TOKENS
// #define PROGRAM 1
// #define VAR 2
// #define BEGIN 3
// #define END 4
// #define END_DOT 5
// #define INTEGER 6
// #define REAL 7
// #define FOR 8
// #define READ 9
// #define WRITE 10
// #define TO 11
// #define DO 12
// #define SEMICOLON 13
// #define COLON 14
// #define COMMA 15
// #define EQUAL 16
// #define ADD 17
// #define SUB 18
// #define MUL 19
// #define DIV 20
// #define OPENBRACKET 21
// #define CLOSEBRACKET 22
// #define ID 23
// #define INT 24
// #define REAL_NUM 25

// Break line into words
vector<string> split_string(string s, string delimiter)
{
    size_t pos = 0;
    string token;
    vector<string> v;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        v.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
    return v;
}

void printCode(int token_code, string token_spec)
{
    // print line number when new line is started
    if (new_line)
    {
        fout << line_no << "\t\t";
        new_line = 0;
    }
    else
    {
        fout << " "
             << "\t\t";
    }

    // print token code
    fout << token_code << "\t\t";

    // print token specification
    if (token_code == 22)
    {
        fout << "^";
    }
    if (token_code == 23)
    {
        fout << "#";
    }

    fout << token_spec << endl;
}

// print all symbols declared in the program
void print_id_table()
{
    id_table.print_table(id_table_file);
}

// for all the symbols in idlist, 
// declare them by specifying type
// if symbol already present then return -1
int declare_type(const char *str, num_type type)
{
    string s = str;
    int res = 1;
    vector<string> ids = split_string(s, ",");
    for (string id : ids)
    {
        if (id_table.insert(id, type) == 0)
            res = -1;
    }
    return res;
}

// for all the symbols in idlist, 
// check if they are declared
int verify_ids(const char *str)
{
    string s = str;
    vector<string> ids = split_string(s, ",");
    for (string id : ids)
    {
        if (id_table.get_type(id) == not_defined)
            return -1;
    }
    return 1;
}

// get type of symbol
num_type getType(const char *str)
{
    return id_table.get_type(str);
}

#endif
