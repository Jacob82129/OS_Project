#include "sdisk.h"


using namespace std;

Sdisk::Sdisk()
{
    
}

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{   //creates the creation of the disk
    this -> diskname = diskname;
    this -> numberofblocks = numberofblocks;
    this -> blocksize = blocksize;

    //check if diskname exits
    ifstream indisk;
    indisk.open(diskname.c_str());
    if(indisk.fail())
    {
        indisk.close();
        ofstream outdisk;
        outdisk.open(diskname.c_str());
        
        for(int i = 0; i < numberofblocks*blocksize; i++) // while(blocksize == numberofblocks)
        {
            
            outdisk.put('#');
        }
    }
    
    else
    {
        ifstream infile;
        infile.open(diskname.c_str());
        int counter = 0;
        
        char c;
        infile.get(c);

        while(infile.good())
        {
            counter++;
            infile.get(c);
        }
        //write blocksize * numberofblocks to diskname
        if(counter == numberofblocks * blocksize)
            cout << "Disk size is correct" << endl;
    }
};

int Sdisk::putblock(int blocknumber, string buffer)
{
        ofstream iofile;
        iofile.open(diskname.c_str());
        if(blocknumber < 0 || blocknumber >= numberofblocks)
        {
            cout << "Block doesn't exist" << endl;
            return 0;
        }

        iofile.seekp(blocksize * blocknumber);

        for(int i=0; i < blocksize; i++)
        {
            iofile.put(buffer[i]);
        }

        return 1;
}

int Sdisk::getblock(int blocknumber, string& buffer)
{
    ifstream iofile;
    iofile.open(diskname.c_str());

    if(blocknumber < 0 || blocknumber >= numberofblocks)
    {
        cout << "Block doesn't exist" << endl;
        return 0;
    }

    iofile.seekg(blocknumber * blocksize);
    buffer.clear();
    char c;

    for(int i = 0; i < blocksize; i++)
    {
        iofile.get(c);
        buffer.push_back(c);
    }

    return 1;
}

int Sdisk::getnumberofblocks()
{
    return numberofblocks;
}

int Sdisk::getblocksize()
{
    return blocksize;
}