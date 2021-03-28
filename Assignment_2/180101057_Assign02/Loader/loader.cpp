#include "loader.h"

// get program address from the user
int getProgramAddress()
{
    string addr = "4000";
    PROGADDR = strtol(addr.c_str(), NULL, 16);
    return 1;
}

// search for text record containing code at num_addr
int search_textrec(vector<textrec> textrecords, int num_addr)
{
    for (int i = 0; i < textrecords.size() - 1; i++)
    {
        if (textrecords[i + 1].firstaddr > num_addr)
            return i;
    }
    return textrecords.size() - 1;
}
