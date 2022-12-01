#include "filesys.h"
#include "sdisk.h"
#include "block.h"


using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize)
{
    this -> diskname = diskname;
    this -> numberofblocks = numberofblocks;
    this -> blocksize = blocksize;

   rootsize = getblocksize() / 12;
   fatsize = (getnumberofblocks() * 5) / getblocksize() + 1;

   string buffer;
   getblock(1, buffer);

   if(buffer[0] == '#')
   {
       buildfs();
       fssynch();
   }
    
    else
    {
        readfs();
    }
}

int Filesys::buildfs()
{
    for(int i = 0; i < rootsize; i++)
    {
        filename.push_back("XXXXXX");
        firstblock.push_back(0); // root has been created
    }

    // 2 + fatsize is first datablock

    fat.push_back(2 + fatsize);
    fat.push_back(-1); // -1 since next entry is reserved for ROOT

    for(int i = 0; i < fatsize; i++)
    {
        fat.push_back(-1); // allocating the blocks for FAT
    }

    for(int i = 2 + fatsize; i < getnumberofblocks(); i++)
    {
        fat.push_back(i+1); // initializes the available spots for next open blocks
    }

    fat[fat.size() - 1] = 0; // signifies the end of useable blocks, end of freelist, try putting -1 instead of 0

    return 0;
}

int Filesys::fssynch()
{
    //synch the file system
    ostringstream outstream1;

    for(int i = 0; i < firstblock.size(); i++)
    {
        outstream1 << filename[i] << " " << firstblock[i] << " ";
    }

    ostringstream outstream2;

    for(int i = 0; i < fat.size();i++)
    {
        outstream2 << fat[i] << " ";
    }

    string buffer1 = outstream1.str(); //buffer1 and buffer2 now contain FAT data
    string buffer2 = outstream2.str();

    //cout << buffer1 << " " << buffer2 << endl;

    // do some blocking
    vector<string> blocks1 = block(buffer1, getblocksize());
    vector<string> blocks2 = block(buffer2, getblocksize());

    putblock(1, blocks1[0]); //block1 on disk

    for(int i = 0; i < blocks2.size();i++)
    {
        putblock(fatsize + 2 + i, blocks2[i]);
    }

    return 1;
    
}

int Filesys::readfs()
{

    cout << "Root is being read..." << endl;

    rootsize = getblocksize()/13;
    fatsize = (getnumberofblocks() * 4 / getblocksize()) + 1;

     istringstream instream1;
     
     string buffer;
     instream1.str(buffer);

     for(int i = 0; i < rootsize;i++)
     {
         string f;
         int b;
         
         instream1 >> f >> b;
         filename.push_back(f);
         firstblock.push_back(b);
     }
     

     cout << "FAT is being read..." << endl;

     istringstream instream2;
     buffer.clear();

     for(int i = 0; i < fatsize;i++)
     {
         string b;
         getblock(i+2,b);
         buffer += b;
     }

     instream2.str(buffer);

     // lets get the FAT
     for(int i = 0; i < getnumberofblocks(); i++)
     {
         int k;
         instream2 >> k;
         fat.push_back(k);
     }

     cout << "Disk has been read. ROOT and FAT have been created" << endl;

     return 1;
     

}

int Filesys::fsclose()
{
    //does nothing
    return 0;
}

int Filesys::newfile(string file)
{
    //creates empty file
    //-1 file already exists; can overwrite
    //0 no room left to create file
    //1 everything is good

    for(int i = 0; i < filename.size();i++)
    {
        if(filename[i] == file)
        {
            return -1;
        }
    }

    for(int i = 0;i < filename.size();i++)
    {
        if(filename[i] == "XXXXXX")
        {
            filename[i] = file;
            firstblock[i] = 0;
            fssynch();
            return 1;
        }
    }

    return 0;
}

int Filesys::rmfile(string file)
{
    //deletes an empty file
    //-1 file doesn't exist
    //0 file not empty
    //1 okay

    for(int i = 0; i < filename.size();i++)
    {
        if(filename[i] == file)
        {
            if(firstblock[i] == 0)
            {
                filename[i] == "XXXXXX";
                fssynch();
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    return -1; // file not found
}

int Filesys::getfirstblock(string file)
{
    //-1 file doesn't exist
    //return firstblock numberoffile

    for(int i = 0; i < filename.size();i++)
    {
        if(filename[i] == file)
        {
            return firstblock[i];
        }
    }

    return -1;//file does not exists
}

int Filesys::addblock(string file, string block)
{
    // returns block number of allocated block
    int allocate = fat[0];
    if(allocate <= 0)
    {
        cout << "No space on disk" << endl; 
        return 0; // 0 indicates failure
    }

    int blockid = getfirstblock(file);
    if(blockid == -1)
    {
        cout << "File does not exists" << endl;
        return 0;
    }

    if(blockid == 0)
    {
        //update the root directory
        for(int i = 0; i < filename.size(); i++)
        {
            if(filename[i] == file)
            {
                firstblock[i] = allocate;
                break;
            }
        }
    }
    else// update the FAT, find the end of file
    {
        while(fat[blockid] != 0)
        {
            blockid = fat[blockid];
        }
        //FAT of blockid fat[blockid] == 0
        fat[blockid] = allocate;
    }

    fat[0] = fat[fat[0]]; // updates free list
    fat[allocate] = 0;// updates FAT
    fssynch();

    //string buffer;
    putblock(allocate, block);

    return allocate;
}

int Filesys::delblock(string file, int blocknumber)
{   
    //1: successful
    //0: failed

    bool flag = fbcheck(file, blocknumber);

    if(!flag)
    {
        return 0;
    }
    
    int b = getfirstblock(file);

    if(b == blocknumber)
    {
        //deleting firstblock in file
        for(int i = 0; i < filename.size(); i++)
        {
            if(filename[i] == file)
            {
                firstblock[i] = fat[firstblock[i]];
                break;
            }
        }
    }
    else //not the firstblock
    {
        while(fat[b] != blocknumber)
        {
            b = fat[b];
        }

        fat[b] = fat[blocknumber];
    }

    fat[blocknumber] = fat[0];
    fat[0] = blocknumber;

    return 1;
}

int Filesys::readblock(string file, int blocknumber, string& buffer)
{
    if(fbcheck(file, blocknumber))
    {
        getblock(blocknumber, buffer);
        return 1;
    }
    else
    {
        return 0;
    }
}

int Filesys::writeblock(string file, int blocknumber, string buffer)
{
    if(fbcheck(file, blocknumber))
    {
        putblock(blocknumber, buffer);
        return 1;
    }
    

    return 0;
}

int Filesys::nextblock(string file, int blocknumber)
{
    //return next block in the file after blocknumber
    if(fbcheck(file, blocknumber))
    {
        return fat[blocknumber];
    }
    else
    { 
        return -1;// if error occurs
    }

    
}

bool Filesys::fbcheck(string file, int blocknumber)
{
    int b = getfirstblock(file);

    if(b == -1)
    {
        return false;
    }
        

    while(b != 0)
    {
        if(b == blocknumber)
        {
            return true;
        }
        else
        {
            b = fat[b];
        }
    }

    return false;
}

void Filesys::printfileName()
{
    for(int i = 0; i < filename.size(); i++)
    {
        cout << i << " : " << filename[i] << endl;

    }
    cout << endl;
}

vector<string> Filesys::ls()
{
    vector<string> flist;

    for(int i = 0; i < filename.size(); i++)
    {
        if(filename[i] != "XXXXX")
        {
            flist.push_back(filename[i]);
        }
    }

    return flist;
}
