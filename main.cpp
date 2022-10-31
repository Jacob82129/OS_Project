#include "sdisk.h"
#include "filesys.h"
#include "block.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  /*
  Sdisk disk1("test1",16,32);
  string block1, block2, block3, block4;
  for (int i=1; i<=32; i++) block1=block1+"1";
  for (int i=1; i<=32; i++) block2=block2+"2";
  disk1.putblock(4,block1);
  disk1.getblock(4,block3);
  cout << "Should be 32 1s : ";
  cout << block3 << endl;
  disk1.putblock(8,block2);
  disk1.getblock(8,block4);
  cout << "Should be 32 2s : ";
  cout << block4 << endl;
  */
 
  Sdisk disk1("disk1",256,128);
  Filesys fsys("disk1",256,128);
  fsys.newfile("file1");
  fsys.newfile("file2");

  string bfile1;
  string bfile2;

  for(int i=1; i<=1024; i++)
  {
    bfile1 += "1";
  }

  vector<string> blocks = block(bfile1,128); 

  int blocknumber=0;

  fsys.printfileName();

  for(int i=0; i< blocks.size(); i++)
  {
    blocknumber=fsys.addblock("file1",blocks[i]);
  }

  fsys.delblock("file1",fsys.getfirstblock("file1"));

  for(int i=1; i<=2048; i++)
  {
    bfile2+="2";
  }

  blocks=block(bfile2,128); 

  for(int i=0; i< blocks.size(); i++)
  {
    blocknumber=fsys.addblock("file2",blocks[i]);
  }

  fsys.delblock("file2",blocknumber);

  
}