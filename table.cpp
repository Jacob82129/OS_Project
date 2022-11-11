#include "table.h"
#include "sdisk.h"
#include "filesys.h"
#include "block.h"

using namespace std;

Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile): Filesys(diskname, numberofblocks, blocksize)
{
    this -> flatfile = flatfile;
    this -> indexfile = indexfile;
}

int Table:: build_Table(string inputfile)
{
    newfile(indexfile);
    newfile(flatfile);

    ifstream infile;
    infile.open(inputfile.c_str()); //open data file
    ostringstream outstream;// rewriting the indexfile

    //read every record from the input file
    string rec; // process each line in indexfile
    getline(infile, rec);// reads the first line up

    while(infile.good())
    {
        string date = rec.substr(0, 5);
        vector<string> blocks = block(rec, getblocksize());

        int b = addblock(flatfile, blocks[0]);
        outstream << date << " " << b << " " << endl;

        getline(infile, rec);
    }
    
    outstream << "88888" << 0 << " " << endl;
    string buffer = outstream.str(); // something missing
    vector<string> blocks = block(buffer, getblocksize());

    for(int i = 0; i < blocks.size(); i++)
    {
        addblock(indexfile, blocks[i]);
    }

    return 1;
}

int Table::search(string value)
{
    int block = indexSearch(value);
    if(block == 0)
    {
        cout << "Record not found." << endl;
        return 0;
    }
    else
    {
        string buffer;
        int error = readblock(flatfile, block, buffer);
        cout << buffer << endl;

        return 1;
    }

    
}

int Table::indexSearch(string value)
{
    string buffer;
    int block = getfirstblock(indexfile);
    while(block != 0)
    {
        string b;
        int error = readblock(indexfile, block, b);
        buffer += b;
        block = nextblock(indexfile, block);
    }

    istringstream instream;
    string s;
    int b;

    instream.str(buffer);
    instream >> s >> b;

    while(s != "88888")
    {
        if(s == value)
        {
            return b;
        }

        instream >> s >> b;
    }

    return 0;
    
}