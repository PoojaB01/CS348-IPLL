%{
    #define MAX_SIZE 1024
    #define MAXLEN 100

    // used to check if token is first word in a line
    int new_line = 1;

    // indicates current line number
    int line_no = 1;

    void printCode(int);

    // specify name of output file
    char *outputFile = "lex_output.txt";
    char *id_table_file = "id_table.txt";
    char *int_table_file = "int_table.txt";

    // pointer to output file
    FILE *fout;

    // data structure to store ids
    char id_table[MAX_SIZE][MAXLEN];
    int id_table_size = 0;

    // data structure to store ints
    char int_table[MAX_SIZE][MAXLEN];
    int int_table_size = 0;
    
%}

alpha   [a-zA-z]
digit   [0-9]
number  {digit}+
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
                // print token code
                printCode(1);
                fprintf(fout, " \n");
            }

"VAR"       {
                // print token code
                printCode(2);
                fprintf(fout, " \n");
            }

"BEGIN"     {
                // print token code
                printCode(3);
                fprintf(fout, " \n");
            }

"END"       {
                // print token code
                printCode(4);
                fprintf(fout, " \n");
            }
            
"END."      {
                // print token code
                printCode(5);
                fprintf(fout, " \n");
            }
            
"INTEGER"   {
                // print token code
                printCode(6);
                fprintf(fout, " \n");
            }
            
"FOR"       {
                // print token code
                printCode(7);
                fprintf(fout, " \n");
            }
            
"READ"      {
                // print token code
                printCode(8);
                fprintf(fout, " \n");
            }
            
"WRITE"     {
                // print token code
                printCode(9);
                fprintf(fout, " \n");
            }
            
"TO"        {
                // print token code
                printCode(10);
                fprintf(fout, " \n");
            }
            
"DO"        {
                // print token code
                printCode(11);
                fprintf(fout, " \n");
            }
            
";"         {
                // print token code
                printCode(12);
                fprintf(fout, " \n");
            }
            
":"         {
                // print token code
                printCode(13);
                fprintf(fout, " \n");
            }
            
","         {
                // print token code
                printCode(14);
                fprintf(fout, " \n");
            }
            
":="        {
                // print token code
                printCode(15);
                fprintf(fout, " \n");
            }
            
"+"         {
                // print token code
                printCode(16);
                fprintf(fout, " \n");
            }
            
"-"         {
                // print token code
                printCode(17);
                fprintf(fout, " \n");
            }
            
"*"         {
                // print token code
                printCode(18);
                fprintf(fout, " \n");
            }
            
"DIV"       {
                // print token code
                printCode(19);
                fprintf(fout, " \n");
            }
            
"("         {
                // print token code
                printCode(20);
                fprintf(fout, " \n");
            }
            
")"         {
                // print token code
                printCode(21);
                fprintf(fout, " \n");
            }
            
{id}        {
                // print token code
                printCode(22);
                // print id value
                fprintf(fout, "^%s\n", yytext);
                // insert id in id-table
                install_id(yytext);
            }
            
{number}    {
                // print token code
                printCode(23);
                // print int value
                fprintf(fout, "#%s\n", yytext);
                // insert int in number-table
                install_num(yytext);
            }
            
%%


void printCode(int x)
{
    // print line number when new line is started
    if(new_line)
    {
        fprintf(fout, "%d\t\t", line_no);
        new_line = 0;
    }
    else {
        fprintf(fout, " \t\t");
    }
    // print token code
    fprintf(fout, "%d\t\t", x);
}

// called by lex when input is exhausted
int yywrap(void) 
{
    return 1;
}

int install_id(char *symbol) 
{
    int present = 0;
    for(int i = 0; i < id_table_size; i++)
    {
        if(strcmp(symbol, id_table[i]) == 0)
        {
            present = 1;
        }
    }
    if(!present)
    {
        strcpy(id_table[id_table_size++], symbol);
    }
    return present;
}

int install_num(char *number) 
{
    int present = 0;
    for(int i = 0; i < int_table_size; i++)
    {
        if(strcmp(number, int_table[i]) == 0)
        {
            present = 1;
        }
    }
    if(!present)
    {
        strcpy(int_table[int_table_size++], number);
    }
    return present;
}

void print_id_table()
{
    FILE *fo = fopen(id_table_file, "w");
    for(int i = 0; i < id_table_size; i++)
    {
        fprintf(fo, "%s\n", id_table[i]);
    }
    fclose(fo);
}

void print_int_table()
{
    FILE *fo = fopen(int_table_file, "w");
    for(int i = 0; i < int_table_size; i++)
    {
        fprintf(fo, "%s\n", int_table[i]);
    }
    fclose(fo);
}

int main()
{
    fout = fopen(outputFile, "w");

    // print table headers
    fprintf(fout, "Line\tToken type\tToken Specifier\n");

    // entry-point for lex
    yylex();

    print_id_table();
    print_int_table();

    fclose(fout);
    return 1;
}