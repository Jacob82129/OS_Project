#include "shell.h"
#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;


Shell::Shell(string filename, int numberofblocks, int blocksize): Filesys(diskname, numberofblocks, blocksize)
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
     
    return 1;
}

int Shell::add(string file, string buffer)
{
    /*
    string filename;

    int code = newfile(filename);

    if(code == 1)
    {
        vector<string> blocks = block(buffer, getblocksize());

        for(int i = 0; i < blocks.size(); i++)
        {
            code = addblock(filename, blocks[i]);
            return 1;
        }
    }
    
        return 0;
    
    */

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

        int error = readblock(file, block, t);
        buffer += t;
        block = nextblock(file, block);
    }

    cout << buffer << endl;
    cout << buffer.length() << endl;

    return 1;
}

int Shell::copy(string file1, string file2)
{
    int code = getfirstblock(file1);

    if(code == -1)
    {
        cout << "File Does Not Exist" << endl;
        return -1;
    }

    int code2 = getfirstblock(file2);

    if(code2 != -1)
    {
        cout << "File Already Exists" << endl;
        return -1;
    }

    int code3 = newfile(file2);

    if(code3 == 0)
    {
        cout << "File does not have space for ROOT" << endl;
        return -1;
    }

    int point = code; // point variable is the firstblock
    while(point != 0)
    {
        string b;
        readblock(file1, point, b);

        int code4 = addblock(file2, b);
        if(code4 == -1)
        {
            cout << "No Space Left" << endl;
            del(file2);
            
            return -1;
        }

        point = nextblock(file1, point);
    }

    return 1;
}