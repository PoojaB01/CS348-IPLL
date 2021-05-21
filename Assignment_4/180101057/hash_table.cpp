#include <bits/stdc++.h>
#include "pascal.h"
using namespace std;

// enumeration of data types
enum num_type
{
    integer_num,
    real_num,
    not_defined
};

// structure for link list
struct link_list
{
    string value;
    num_type type;
    link_list *next;

    link_list(string value, num_type type)
    {
        this->value = value;
        this->type = type;
        next = NULL;
    }
};

// hash table class
class hash_table
{
    vector<link_list *> table;
    int size;

    // generate hash value for string
    // sum of ascii codes of characters modulo size
    int get_hash_val(string s)
    {
        int hash = 0;
        for (int i = 0; i < s.length(); i++)
        {
            hash = (hash + s[i]) % size;
        }
        return hash;
    }

public:
    // hash table constructor
    hash_table(int size)
    {
        this->size = size;
        this->table = vector<link_list *>(size, NULL);
    }

    // function to insert a value in hash table
    int insert(string value, num_type type)
    {
        // check if value already present
        if (search(value))
        {
            return 0;
        }

        // else insert in hash table
        int index = get_hash_val(value);
        link_list *new_node = new link_list(value, type);
        new_node->next = table[index];
        table[index] = new_node;
        return 1;
    }

    // get the type of entry with key value
    num_type get_type(string value)
    {
        int index = get_hash_val(value);
        link_list *temp = table[index];
        while (temp != NULL)
        {
            if (temp->value == value)
            {
                return temp->type;
            }
            temp = temp->next;
        }
        return not_defined;
    }

    // function to search for a value in hash table
    int search(string value)
    {
        int index = get_hash_val(value);
        link_list *temp = table[index];
        while (temp != NULL)
        {
            if (temp->value == value)
            {
                return 1;
            }
            temp = temp->next;
        }
        return 0;
    }

    // function to print all values in
    // hash table in a file
    void print_table(string filename)
    {
        ofstream fout;
        fout.open(filename, ios_base::out);
        for (int i = 0; i < size; i++)
        {
            link_list *temp = table[i];
            while (temp)
            {
                fout << temp->value << ' ' << temp->type << endl;
                temp = temp->next;
            }
        }
        fout.close();
    }
};
