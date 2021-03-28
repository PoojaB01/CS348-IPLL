#ifndef assembler
#define assembler

#include <bits/stdc++.h>
using namespace std;

#define MAXS 1024
#define MAXW 10

#define ILEN 1 // Instruction length
#define WLEN 1 // Word length

int ERROR_FLAG = 0;

int PROGLEN;         // store program length
char PROGNAME[MAXS]; // store program length
int STARTADDR;       // store program length

// to store information about opcode
struct opcode_info
{
    string addr;
    int format;
};

// to store information about symbol
struct symbol_info
{
    string addr;
};

// to store modification records
struct modrec
{
    int addr;
    int length;
    bool sign;
    string symbol;
};

// symbol table class
class symtab
{
    unordered_map<string, symbol_info> table; // symbol table
    set<string> extref;                       // list of external reference symbols
    set<string> extdef;                       // list of external definition symbols
    int length;                               // length of section

public:
    symtab();
    symbol_info *search_symtab(const char *LABEL);
    int insert_symtab(const char *LABEL, int LOCCTR);
    int insert_extdef(char *LABEL);
    int insert_extref(char *LABEL);
    bool is_extref(const char *SYMBOL);
    int print_symtab();
    void set_length(int length);
    int get_length();
};

unordered_map<string, opcode_info> optab; // to store opcode table
map<string, symtab *> symtab_list;        // to store list of symbol table for each section
set<string> literal_pool;                 // to store all the unique literals encountered in program

map<string, string> register_list = // contains register codes
    {
        {"A", "0"},
        {"X", "1"},
        {"L", "2"},
        {"B", "3"},
        {"S", "4"},
        {"T", "5"},
        {"F", "6"},
        {"PC", "8"},
        {"SW", "9"},
};

// Utility files
const char *SYMTAB = "symbolTable.txt";
const char *OPTAB = "opcodeTable.txt";
const char *INTM = "intermediate.txt";

// Utility functions
int break_line(char *str, int start, char *words[], const char *delimiter = " ");
opcode_info *search_optab(char *OPCODE);
int print_literals(int LOCCTR, FILE *outputFile, symtab *base);
int handle_operand(char *OPERAND, queue<modrec> &modification_records, symtab *base, int oplen, int addr);

// Funtions for pass 1 and 2
int pass_one(FILE *inputFile, FILE *outputFile);
int pass_two(FILE *inputFile, FILE *outputFile, FILE *listingFile);

#endif
