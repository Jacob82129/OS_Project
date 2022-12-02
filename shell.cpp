#include "shell.h"
#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;

Shell::Shell() : Filesys(diskname, numberofblocks, blocksize)
{
    //default constructor
}


Shell::Shell(string diskname, int numberofblocks, int blocksize): Filesys(diskname, numberofblocks, blocksize) //inherits Filesys and Sdisk
{
    cout << "Shell has been created" << endl;   // creates the shell
}

int Shell::dir()
{
    vector<string> flist = ls(); // utilizes the ls function with Filesys

    for(int i = 0; i < flist.size(); i++)
    {
        cout << flist[i] << endl;   //displays contents of flist
    }
     
    return 0;
}

int Shell::add(string file, string buffer)
{


    int code = newfile(file); // creates new file from parameter file

    if(code == 1)
    {
        vector<string> blocks = block(buffer, getblocksize());

        for(int i = 0; i < blocks.size(); i++)
        {
            code = addblock(file, blocks[i]); // adds each consecutive block towards the file
            return 1;
        }
    }
    
        return 0; // return 0 when fail
    
}

int Shell::del(string file)
{
    
    while(getfirstblock(file) != 0)
    {
        delblock(file, getfirstblock(file)); // delblock will function when file is not empty
    }
 
    rmfile(file); // deletes the empty file

    return 1;
}

int Shell::type(string file) // will display the contents of a file
{
    int block = getfirstblock(file);

    string buffer;
    while(block > 0)
    {
        string t;

        readblock(file, block, t);
        buffer += t; // stores value of t onto buffer
        block = nextblock(file, block);
    }

    cout << buffer << endl; //displays the contents
    cout << buffer.length() << endl;

    return 0;
}

int Shell::copy(string file1, string file2)
{   
   string buffer;

   int block = getfirstblock(file1);

    while(block > 0)
    {
        string b;
        readblock(file1, block, b);
        buffer += b; // stores values of b onto buffer
        block = nextblock(file1, block);
    }

    add(file2, buffer); // copies contents of file1 to file2

    return 0;
}