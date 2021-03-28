#include "loader.h"

// Pass 1
// Takes object code as input
// and generates ESTAB
int pass_one(ifstream &fin)
{
    // get program address from user
    getProgramAddress();

    ofstream fout;
    fout.open(estabfile, ios_base::out);
    fout << "ControlSec\tSymbolName\tAddr\tLength" << endl;

    // set CSADDR to PROGADDR
    CSADDR = PROGADDR;
    string record;
    while (fin.good())
    {
        // read header record
        getline(fin, record);
        if (record.length() == 0)
            break;
        string csname = record.substr(1, 6);
        string length = record.substr(13, 6);

        // set CSLTH to control section length
        CSLTH = (int)strtol(length.c_str(), NULL, 16);

        // search csname in estab
        if (ESTAB.find(csname) != ESTAB.end())
        {
            cout << "Error: Duplicate external symbol." << endl;
            ERROR_FLAG = 1;
            return -1;
        }
        else
        {
            fout << csname << "\t\t\t";
            fout << std::uppercase << ::setfill('0') << std::setw(4) << std::hex << CSADDR << "\t";
            fout << std::uppercase << ::setfill('0') << std::setw(4) << std::hex << CSLTH << endl;

            // insert csname in estab
            ESTAB[csname] = CSADDR;
        }
        while (record[0] != 'E')
        {
            // read next input line
            getline(fin, record);
            if (record[0] == 'D')
            {
                // iterate over all symbols in record
                for (int i = 1; i < record.length() - 1; i += 12)
                {
                    string symbol = record.substr(i, 6);
                    string addr = record.substr(i + 6, 6);

                    // search estab for symbol
                    if (ESTAB.find(symbol) != ESTAB.end())
                    {
                        cout << "Error: Duplicate external symbol.1" << endl;
                        ERROR_FLAG = 1;
                    }
                    else
                    {
                        fout << "\t\t" << symbol << "\t";
                        fout << std::uppercase << ::setfill('0') << std::setw(4) << std::hex << CSADDR + (int)strtol(addr.c_str(), NULL, 16) << endl;
                        // insert symbol in estab
                        ESTAB[symbol] = CSADDR + (int)strtol(addr.c_str(), NULL, 16);
                    }
                }
            }
        }
        getline(fin, record);
        getline(fin, record);

        // add control section length to control section address
        CSADDR += CSLTH;
    }
    fout.close();
    cout << "PASS ONE COMPLETED." << endl;
    return 1;
}