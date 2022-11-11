#ifndef TABLE_H
#define TABLE_H

#include "sdisk.h"
#include "filesys.h"
#include "block.h"
#include "shell.h"

class Table: public Filesys
{
    public:

    Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile);
    int build_Table(string input_file);
    int search(string value);

    private:
    string flatfile;
    string indexfile;
    int indexSearch(string value);


};
#endif
