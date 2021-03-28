/*
IPLL Assignment 2
Author: Pooja Bhagat

Environment used to run the program :  
`gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)` 

Command to compile:  
`g++ -o loader main.cpp`
   
Command to run the code:  
`./loader`
*/

#include "loader.h"
#include "loader.cpp"
#include "pass_one.cpp"
#include "pass_two.cpp"

int main(int argc, char *argv[])
{
    ifstream fin;
    ofstream fout;

    // open input file
    fin.open(inputFile, ios_base::in);
    // open output file
    fout.open(outputFile, ios_base::out);
    
    if (!fin.is_open() || !fout.is_open())
    {
        cout << "Error opening files." << endl;
    }

    // call pass one
    if (pass_one(fin) < 0)
    {
        cout << "Error in pass one." << endl;
        fin.close();
        return 0;
    }

    fin.close();
    fin.open(inputFile, ios_base::in);

    // call pass two
    if (pass_two(fin, fout) < 0)
    {
        cout << "Error in pass two." << endl;
        fin.close();
        return 0;
    }

    cout << "LOADING SUCCESSFUL." << endl;
    cout << "ERROR_FLAG = " << ERROR_FLAG << endl;
    cout << "Check loaderOutput.txt" << endl;
    
    fin.close();
    fout.close();
    return 0;
}