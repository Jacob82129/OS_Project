#include "shell.h"
#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;

Shell::Shell()
{

}

Shell::Shell(string filename, int numberofblocks, int blocksize)
{
    this -> filename = filename;
    this -> numberofblocks = numberofblocks;
    this -> blocksize = blocksize;
}

int Shell::dir()
{
    vector<string> flist = ls();

    for(int i = 0; i < flist.size(); i++)
    {
        cout << flist[i] << endl;
    }
     
    return 0;
}

int Shell::add(string file, string buffer)
{

    return 0;
}

int Shell::del(string file)
{
    return 0;
}

int Shell::type(string file)
{
    return 0;
}

int Shell::copy(string file1, string file2)
{
    return 0;
}