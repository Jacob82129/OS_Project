#ifndef FILESYS_
#define FILESYS_
#include "sdisk.h"
#include "block.h"


using namespace std;

class Filesys: public Sdisk
{
    public:
        Filesys(string diskname, int numberofblocks, int blocksize);
        int fsclose(); //runs fssynch();
        int newfile(string file);
        int rmfile(string file);// remove blocks in the file
        int getfirstblock(string file);// accessor function to find what first block is
        int addblock(string file, string block);// to create file, add block sequence to file
        int delblock(string file, int blocknumber);// take file in blocknumber, delete block# in file
        int readblock(string file, int blocknumber, string& buffer);
        int writeblock(string file, int blocknumber, string buffer);// write block to the disk
        int nextblock(string file, int blocknumber);// uses getsfirstblock(), then reads the next block
        
        void printfileName();


    protected:
        
        int rootsize;
        int fatsize;
        vector<string> filename;
        vector<int> firstblock;
        vector<int> fat;
        int buildfs();
        int readfs();
        int fssynch();
        bool fbcheck(string file, int blocknumber);
};
#endif