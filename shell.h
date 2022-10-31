#ifndef SHELL_H
#define SHELL_H

#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;

class Shell: public Filesys
{
    public:
        Shell(string filename, int numberofblocks, int blocksize);
        int dir();
        int add(string file, string buffer);
        int del(string file);
        int type(string file);
        int copy(string file1, string file2);
};
#endif