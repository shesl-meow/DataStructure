#include <iostream>
#include <string>
#include "Header.h"
#include "HashString.h"
using namespace std;

Coding::HuffmanCoding hc;
char zero = '0', one = '1';

void ExeCommand(string pseudo_command);
void PseudoShell(){
  cout <<
	"-----------------------------------------\n"
	"- Hello There!		/\\	/\\	-\n"
	"- This is pseudo-shell	|  ^^^^	 |	-\n"
	"- Used to test huffman	\\  o  o  /	-\n"
	"- see `help` for help	 |  ==	|	-\n"
	"- 			  \\____/	-\n"
	"-----------------------------------------\n";
  string pseudo_command = "";
  cout << "$ ";
  while(cin >> pseudo_command)
    ExeCommand(pseudo_command);
}

void help();
void assign();
void text(){ cout << hc.read_text(); }
void table(){ cout << hc.read_char_times(); }
void tree(){ cout << hc.read_coding_tree(); }
void encode();
void decode();
void ExeCommand(string pseudo_command)
{
  switch (hash_(pseudo_command.c_str())) {
    case "help"_hash: help(); break;
    case "assign"_hash: assign(); break;
    case "text"_hash: text(); break;
    case "table"_hash: table(); break;
    case "tree"_hash: tree(); break;
    case "encode"_hash: encode(); break;
    case "decode"_hash: decode(); break;
    case "exit"_hash: exit(0); break;
    default: help(); break;
  }
  cout << endl << "$ ";
}

void help()
{
  string manual=
    "[help]  : see help manual.\n"
    "[assign]: assign string for huffman encoding.\n"
    "[text]  : read current text string for encoding or decode result.\n"
    "[table] : read the character occurence times.\n"
    "[tree]  : read huffman coding tree.\n"
    "[encode]: begin to encode text via huffman coding.\n"
    "[decode]: begin to decode text via huffman coding.\n";
  cout << manual;
}

void assign()
{
  cout << "Enter a multiple lines article or one line statement?(m/o)";
  string tmp;
  while(cin >> tmp)
  {
    cin.get();
    if(tmp == "m"){
      cout << "Please enter a string for encoding (enter `_EOF_` to terminate):" << endl;
      string article = "", buffer = "";
      while(getline(cin, buffer))
        if(buffer == "_EOF_") break;
        else{
          article += (buffer + '\n');
          buffer = "";
        }
      hc.assign_text(article);
      break;
    }
    if(tmp == "o"){
      string stat = "";
      getline(cin, stat);
      hc.assign_text(stat);
      break;
    }
    cout << "Illegal please enter `m` or `o`\n"
      "Enter a multiple lines article or one line statement?(m/o)";
  }
  hc.init_coding_tree();
}

void encode()
{
  cout << "You can set the encode character for encode.\n";
  cout << "SET?(y/n)";
  string tmp = "";
  while(cin >> tmp){
    if(tmp == "y"){
      cout << "- First char represent zero(0) in byte default '0'\n"
        "- Second char represent one(1) in byte default '1'\n"
        "Enter your left and right character for encode(example: `LR`):";
      cin >> zero >> one;
      break;
    }
    if(tmp == "n") break;
    cout << "Illegal input, please enter again.\n\nSET?(y/n)";
  }
  hc.encode(zero, one);
  cout << "Encode result:" << hc.read_text() << endl;
}

void decode()
{
  cout << "cipher_text: " << hc.read_text() << endl;
  hc.decode(zero, one);
  cout << "Decode result: " << hc.read_text() << endl;
}
