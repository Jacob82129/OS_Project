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
    fstream disk;
    disk.open(this -> diskname.c_str(), ios::in);

    if(disk.fail()) //check if the file fails to open
    {
        
        disk.open(this -> diskname.c_str(), ios::out); // open disk to allow for input

        if(disk.fail())
        {
            return; // exits from making sdisk
        }
        else
        {   // iterates thru the amount of #ofblocks multiplied by the size of each block
            for(int i = 0; i < this -> numberofblocks * this -> blocksize; i++) 
            {
            
                disk.put('#'); // creates allocated space for sdisk
            }   
        }
        
    }

    disk.close();
    
    
};

int Sdisk::putblock(int blocknumber, string buffer)
{
        fstream iofile(this -> diskname.c_str(), ios::in | ios::out); //opens and accepts input for iofile
        
        if(iofile.fail())
        {
            return 0;  //terminates after file fails to open nor write nor read
        }

        if(blocknumber < 0 || blocknumber >= numberofblocks)
        {
            cout << "Block doesn't exist" << endl;
            return 0;
        }

        iofile.seekp(this -> blocksize * blocknumber);

        for(int i=0; i < buffer.length() && i < this -> blocksize; i++)
        {
            iofile.put(buffer[i]);  //inserts buffer into blocknumber
        }

        iofile.close();

        return 1;
}

int Sdisk::getblock(int blocknumber, string& buffer)
{
    fstream iofile;
    iofile.open(this -> diskname.c_str(), ios::in); // opens for input

    if(blocknumber < 0 || blocknumber >= numberofblocks)
    {
        cout << "Block doesn't exist" << endl; //program ends with condition is met
        return 0;
    }

    iofile.seekg(blocknumber * this -> blocksize);
    buffer.clear();
    char c;

    for(int i = 0; i < this -> blocksize; i++)
    {
        iofile.get(c);
        buffer.push_back(c); //adds to the buffer after iterating thru blocksize
    }

    iofile.close();

    return 1;
}

int Sdisk::getnumberofblocks()
{
    return this -> numberofblocks; // returns numberofblocks
}

int Sdisk::getblocksize()
{
    return this -> blocksize; // returns blocksize
}