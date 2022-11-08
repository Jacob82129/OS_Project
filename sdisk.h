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
        Sdisk(string diskname, int numberofblocks, int blocksize); //creates the sdisk with the following parameters
        int getblock(int blocknumber, string& buffer);  // gets blocknumber from disk, then stores to buffer
        int putblock(int blocknumber, string buffer);   // writes buffer into blocknumber
        int getnumberofblocks(); // accessor function
        int getblocksize(); // accessor function

    protected:
        string diskname;
        int numberofblocks;
        int blocksize;

};
#endif