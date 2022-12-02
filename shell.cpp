#include "shell.h"
#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;

Shell::Shell() : Filesys(diskname, numberofblocks, blocksize)
{

}


Shell::Shell(string diskname, int numberofblocks, int blocksize): Filesys(diskname, numberofblocks, blocksize)
{
    cout << "Shell has been created" << endl;
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


    int code = newfile(file);

    if(code == 1)
    {
        vector<string> blocks = block(buffer, getblocksize());

        for(int i = 0; i < blocks.size(); i++)
        {
            code = addblock(file, blocks[i]);
            return 1;
        }
    }
    
        return 0;
    
    
   /*
    newfile(file);

	for(int i = 0; i < 128; i++)   // blockSize = 128
	{
		buffer += '#';
	}

    char x;
    cin.get(x);
    
    while (x != '~') 
    {
        buffer += x;
        cin.get(x);
    }
    
    vector<string> blocked = block(buffer, 128);    // blockSize = 128
    
    for (int i = 0; i < blocked.size(); i++) 
    {
        addblock(file, blocked[i]);
    }

    return 1;
    */
}

int Shell::del(string file)
{
    
    while(getfirstblock(file) != 0)
    {
        delblock(file, getfirstblock(file));
    }
 
    rmfile(file);

    return 1;
}

int Shell::type(string file)
{
    int block = getfirstblock(file);

    string buffer;
    while(block > 0)
    {
        string t;

        readblock(file, block, t);
        buffer += t;
        block = nextblock(file, block);
    }

    cout << buffer << endl;
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
        buffer += b;
        block = nextblock(file1, block);
    }

    add(file2, buffer);

    return 0;
}