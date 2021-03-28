#include "loader.h"

// Pass 2
// Takes object code as input
// and loads it into memory
// with modification
int pass_two(ifstream &fin, ofstream &fout)
{
    fin.seekg(0, fin.beg);

    // set csaddr to progaddr
    CSADDR = PROGADDR;
    // set execaddr to progaddr
    EXECADDR = PROGADDR;
    string record;
    int lastline = 0;

    // data structure to store text records
    // of control section
    vector<textrec> textrecords;

    // data structure representing memory of system
    vector<vector<string>> memory(pow(2, 12), vector<string>(4, "........"));

    while (fin.good())
    {
        // read next input record
        getline(fin, record);
        if (record.length() == 0)
            break;
        string csname = record.substr(1, 6);
        string length = record.substr(13, 6);
        // set control section length
        CSLTH = (int)strtol(length.c_str(), NULL, 16);

        while (record[0] != 'E')
        {

            getline(fin, record);

            // check if text record
            if (record[0] == 'T')
            {
                // get start address of record
                string addr = record.substr(1, 6);
                int start_addr = (int)strtol(addr.c_str(), NULL, 16);

                // insert record in data structure
                textrecords.push_back({start_addr, record});
            }

            // check if modification record
            if (record[0] == 'M')
            {
                string addr = record.substr(1, 6);
                string len = record.substr(7, 2);
                string symbol = record.substr(10, record.length() - 19 - 1);
                while (symbol.length() < 6)
                {
                    symbol = symbol + ' ';
                }

                int num_addr = (int)strtol(addr.c_str(), NULL, 16);

                // search text record in textrecords
                int index = search_textrec(textrecords, num_addr);

                int firstaddr = textrecords[index].firstaddr;
                string rec = textrecords[index].record;
                int num_len = (int)strtol(len.c_str(), NULL, 16);

                // get the required value to change
                string to_change = rec.substr(9 + (num_addr - firstaddr) * 2 + num_len % 2, num_len);
                int value = (int)strtol(to_change.c_str(), NULL, 16);

                if (ESTAB.find(symbol) == ESTAB.end())
                {
                    ERROR_FLAG = 1;
                    return -1;
                }

                // calculate new value
                if (record[9] == '+')
                {
                    value += ESTAB[symbol];
                }
                else
                {
                    value -= ESTAB[symbol];
                }

                stringstream ss;
                ss << hex << value;
                string res = ss.str();
                while (res.length() < num_len)
                    res = '0' + res;

                // modify record
                for (int i = 0; i < num_len; i++)
                {
                    rec[9 + (num_addr - firstaddr) * 2 + num_len % 2 + num_len - i - 1] = toupper(res[res.length() - 1 - i]);
                }
                textrecords[index] = {firstaddr, rec};
            }
        }

        // load control section in memory
        for (int i = 0; i < textrecords.size(); i++)
        {
            for (int j = 0; j < textrecords[i].record.length() - 9; j++)
            {
                int I = ((CSADDR + textrecords[i].firstaddr) * 2 + j) / 32;
                int J = ((CSADDR + textrecords[i].firstaddr) * 2 + j) % 32;
                memory[I][J / 8][J % 8] = textrecords[i].record[j + 9];
                lastline = max(lastline, I);
            }
        }
        textrecords.clear();
        getline(fin, record);
        getline(fin, record);

        // add cslth to csaddr
        CSADDR += CSLTH;
    }
    // print memory
    for (int i = max(PROGADDR / 16 - 1, 0); i < min((int)memory.size(), lastline + 3); i++)
    {
        fout << std::uppercase << ::setfill('0') << std::setw(4) << std::hex << i * 16;
        fout << "    " << memory[i][0] << ' ' << memory[i][1] << ' ' << memory[i][2] << ' ' << memory[i][3] << endl;
    }

    cout << "PASS TWO COMPLETED." << endl;

    return 1;
}