#include "sdisk.h"
#include "filesys.h"
#include "block.h"
#include "shell.h"
#include "table.h"


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
 /*
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

*/
  //It inputs commands as : command op1 op2
 //You should modify it to work for your implementation.
 //
 
  
  string name = "disk";

  Table table = Table(name, 256, 128, "flatfile", "indexfile");

  table.build_Table("data.txt");
  
  Shell shell = Shell(name, 256, 128);
  

  
 
 string s;
 string command="go";
 string op1,op2;

while (command != "quit")
{
       command.clear();
       op1.clear();
       op2.clear();

       cout << "$";
       getline(cin,s);

       int firstblank=s.find(' ');
       if (firstblank < s.length()) s[firstblank]='#';

       int secondblank=s.find(' ');
       command=s.substr(0,firstblank);

       if (firstblank < s.length())
         op1=s.substr(firstblank+1,secondblank-firstblank-1);
       
       if (secondblank < s.length())
         op2=s.substr(secondblank+1);
       
       if (command=="dir")
          {
            // use the ls function
            shell.dir();
          }
       if (command=="add")
          {
            // The variable op1 is the new file and op2 is the file data
            shell.add(op1, op2);
          }
       if (command=="del")
          {
            // The variable op1 is the file
            shell.del(op1);
          }
       if (command=="type")
          {
            // The variable op1 is the file
            shell.type(op1);
          }
       if (command=="copy")
          {
            // The variable op1 is the source file and the variable op2 is the destination file.
            shell.copy(op1, op2);
          }
        if(command == "search")
        {
            table.search(op1);
        }
       
}

 return 0;
  
}