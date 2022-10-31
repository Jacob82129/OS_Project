#ifndef SDISK_H
#define SDISK_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Sdisk
{
    public:
        Sdisk();
        Sdisk(string diskname, int numberofblocks, int blocksize);
        int getblock(int blocknumber, string& buffer);
        int putblock(int blocknumber, string buffer);
        int getnumberofblocks(); // accessor function
        int getblocksize(); // accessor function

    protected:
        string diskname;
        int numberofblocks;
        int blocksize;

};
#endif