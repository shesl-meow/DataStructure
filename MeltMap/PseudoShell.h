#include <iostream>
#include <string>
#include "Display.h"
#include "HashString.h"
using namespace std;

Display::MeltMap mm;

void ExeCommand(string pseudo_command);
void PseudoShell(){
  cout <<
	"-----------------------------------------\n"
	"- Hello There!		/\\	/\\	-\n"
	"- This is pseudo-shell	|  ^^^^	 |	-\n"
	"- Used to test melt-map	\\  o  o  /	-\n"
	"- see `help` for help	 |  ==	|	-\n"
	"- 			  \\____/	-\n"
	"-----------------------------------------\n";
  string pseudo_command = "";
  cout << "$ ";
  while(cin >> pseudo_command)
    ExeCommand(pseudo_command);
}

void help();
void init();
void show(){ cout << string(mm); }
void fill(){ mm.Fill(); }
void melt();
void start();
void ExeCommand(string pseudo_command)
{
  switch (hash_(pseudo_command.c_str())) {
    case "help"_hash: help(); break;
    case "init"_hash: init(); break;
    case "show"_hash: show(); break;
    case "fill"_hash: fill(); break;
    case "melt"_hash: melt(); break;
    case "start"_hash: start(); break;
    case "exit"_hash: exit(0); break;
    default: help(); break;
  }
  cout << endl << "$ ";
}

void help()
{
  string manual=
    "[help]  : see help manual.\n"
    "[init]  : init metal map.\n"
    "[show]  : display the current state.\n"
    "[fill]  : fill with water from the edge.\n"
    "[melt]  : melt metal with water once.\n"
    "[start] : start melt until metal melt out.\n";
  cout << manual;
}

void init(){
  string tips =
    "[TIPS] ' ' stand for empty, '#' stand for metal.\n"
    "[TIPS] Any character other than the two above will exit input.\n"
    "[TIPS] Type `done` to exit input.\n";
  cout << tips << endl;

  string line; list< list<bool> > bl_llst;
  cin.clear();
  fflush(stdin);
  while(true){
    getline(cin, line);
    list<bool> bl_lst;
    for(auto chr: line){
      switch (chr) {
        case '#': bl_lst.push_back(true); break;
        case ' ': bl_lst.push_back(false); break;
        default: goto END;
      }
    }
    bl_llst.push_back(bl_lst);
  }
END:
  cout << bl_llst.size();
  mm.Init(bl_llst);
}

void melt(){
  if(mm.has_water()) mm.Melt();
  else cout << "You should fill water before melt." << endl;
}

void start(){
  cout << "Initial state:" << string(mm);
  if(!mm.has_water()){
    fill();
    cout << "Fill water: " << string(mm);
  }

  uint melt_time = 0;
  uint prev_acount = mm.metal_block_acount();
  while(mm.has_metal()){
    melt(), show(), melt_time++;
    cout << string(melt_time, '.') << endl;

    uint cur_acount = mm.metal_block_acount();
    if(cur_acount < prev_acount) prev_acount = cur_acount;
    else break;
  }

  if(prev_acount == 0) cout << "Metal was melt after " << melt_time << "s" << endl;
  else cout << "This metal can't melt anymore." << endl;
}
