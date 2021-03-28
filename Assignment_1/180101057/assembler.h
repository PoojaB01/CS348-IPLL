#ifndef assembler
#define assembler

#include<bits/stdc++.h>
using namespace std;

#define MAXS 1024
#define MAXW 10

#define ILEN 1          // Instruction length
#define WLEN 1          // Word length

int ERROR_FLAG = 0;

int PROGLEN;            // store program length
char PROGNAME[MAXS];    // store program length
int STARTADDR;          // store program length

unordered_map<string, string> optab;
unordered_map<string, string> symtab;

// Utility files
const char *SYMTAB = "symbolTable.txt";
const char *OPTAB = "opcodeTable.txt";
const char *INTM = "intermediate.txt";

// Utility functions
int break_line(char *str, int start, char *words[]);
const char *search_symtab(char *LABEL);
int insert_symtab(char *LABEL, int LOCCTR);
const char *search_optab(char *OPCODE);

// Funtions for pass 1 and 2
int pass_one(FILE *inputFile, FILE *outputFile);
int pass_two(FILE *inputFile, FILE *outputFile, FILE *listingFile);

#endif
