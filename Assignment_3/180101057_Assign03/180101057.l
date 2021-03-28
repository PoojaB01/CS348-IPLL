%{
#include "180101057_pascal.h"    
#include "180101057_pascal.cpp"
%}

alpha   [a-zA-z]
digit   [0-9]
number  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
id      {alpha}({alpha}|{digit})*

%%
[ \t]       {
                // Do nothing
                // Ignore whitespaces
            }

"\n"        {
                // indicate start of new line
                line_no ++;
                new_line = 1;
            }

"PROGRAM"   { 
                // print output line
                printCode(1);
            }

"VAR"       {
                // print output line
                printCode(2);
            }

"BEGIN"     {
                // print output line
                printCode(3);
            }

"END"       {
                // print output line
                printCode(4);
            }
            
"END."      {
                // print output line
                printCode(5);
            }
            
"INTEGER"   {
                // print output line
                printCode(6);
            }
            
"FOR"       {
                // print output line
                printCode(7);
            }
            
"READ"      {
                // print output line
                printCode(8);
            }
            
"WRITE"     {
                // print output line
                printCode(9);
            }
            
"TO"        {
                // print output line
                printCode(10);
            }
            
"DO"        {
                // print output line
                printCode(11);
            }
            
";"         {
                // print output line
                printCode(12);
            }
            
":"         {
                // print output line
                printCode(13);
            }
            
","         {
                // print output line
                printCode(14);
            }
            
":="        {
                // print output line
                printCode(15);
            }
            
"+"         {
                // print output line
                printCode(16);
            }
            
"-"         {
                // print output line
                printCode(17);
            }
            
"*"         {
                // print output line
                printCode(18);
            }
            
"DIV"       {
                // print output line
                printCode(19);
            }
            
"("         {
                // print output line
                printCode(20);
            }
            
")"         {
                // print output line
                printCode(21);
            }
            
{id}        {
                string id = yytext;

                // print output line
                printCode(22, id);

                // insert id in id-table
                install_id(id);
            }
            
{number}    {
                string number = yytext;

                // print output line
                printCode(23, number);

                // insert num in int_table
                install_num(number);
            }
            
%%

// called by lex when input is exhausted
int yywrap(void) 
{
    return 1;
}

int main()
{
    fout.open(outputFile, ios_base::out);

    // print table headers
    fout << "Line\t\tToken type\tToken Specifier\n";

    // entry-point for lex
    yylex();

    // print hashed tables
    print_id_table();
    print_int_table();

    cout << "Check output files: " << endl;
    cout << outputFile << endl;
    cout << id_table_file << endl;
    cout << int_table_file << endl;
    fout.close();
    return 1;
}