#include "180101057_pascal.h"

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

int install_id(string symbol)
{
    return id_table.insert(symbol);
}

int install_num(string number)
{
    return int_table.insert(number);
}

void print_id_table()
{
    id_table.print_table(id_table_file);
}

void print_int_table()
{
    int_table.print_table(int_table_file);
}
