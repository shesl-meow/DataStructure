#include <iostream>
#include <string>
#include <list>
#include "Header.h"
#include "HashString.h"
using namespace std;

list<double> disorder_seq;

bool is_init = true;
bool is_ascend = true;
double* num_seq;
uint seq_len = 0;

Sort::AbstractSort<double> *sort_ptr = nullptr;
void release(){
  if(sort_ptr != nullptr){
    delete sort_ptr;
    sort_ptr = nullptr;
  }
}


void ExeCommand(string pseudo_command);
void PseudoShell(){
  cout <<
	"-----------------------------------------\n"
	"- Hello There!		/\\	/\\	-\n"
	"- This is pseudo-shell	|  ^^^^	 |	-\n"
	"- Used for sort-method	\\  o  o  /	-\n"
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
void toggle(){ is_ascend = !is_ascend; }
void check();
void detail();
void reset();
void ExeCommand(string pseudo_command)
{
  switch (hash_(pseudo_command.c_str())) {
    case "help"_hash: help(); break;
    case "assign"_hash: assign(); break;
    case "toggle"_hash: toggle(); break;
    case "Bubble"_hash: release(); sort_ptr=new Sort::BubbleSort<double>(num_seq, seq_len, is_ascend); break;
    case "Insert"_hash: release(); sort_ptr=new Sort::InsertSort<double>(num_seq, seq_len, is_ascend); break;
    case "Select"_hash: release(); sort_ptr=new Sort::SelectionSort<double>(num_seq, seq_len, is_ascend); break;
    case "Merge"_hash: release(); sort_ptr=new Sort::MergeSort<double>(num_seq, seq_len, is_ascend); break;
    case "Shell"_hash: release(); sort_ptr=new Sort::ShellSort<double>(num_seq, seq_len, is_ascend); break;
    case "check"_hash: check(); break;
    case "detail"_hash: detail(); break;
    case "reset"_hash: reset(); break;
    case "exit"_hash: exit(0); break;
    default: help(); break;
  }
  cout << endl << "$ ";
}

void help()
{
  string manual=
    "[help]  : see help manual.\n"
    "[assign]: assign the number sequence for sort usage.\n"
    "[detail]: display the sort detail.\n"
    "[toggle]: toggle status between ascend and descend.\n"
    "[Bubble]: apply bubble sort on the current sequence.\n"
    "[Insert]: apply insert sort on the current sequence.\n"
    "[Select]: apply select sort on the current sequence.\n"
    "[Merge] : apply merge sort on the current sequence.\n"
    "[Shell] : apply shell sort on the current sequence.\n"
    "[check] : check the sort result.\n"
    "[detail]: display the detail of latest sort method.\n"
    "[reset] : disorder the ordered sequence to the begining state.\n";
  cout << manual;
}

void assign()
{
  cout << "Assign the list waiting to be sorted, any illegal input will end input." << endl;
  double tmp;
  while(cin >> tmp) disorder_seq.push_back(tmp);
  cin.clear(); // The cin stream corrupt while get illegal char.
  reset();
}

void check(){
  if(sort_ptr == nullptr){
    for(uint i = 0; i < seq_len; ++i)
      cout << num_seq[i] << " ";
    cout << endl;
  }else sort_ptr->display(cout);
}

void detail(){
  if(sort_ptr == nullptr){
    cout << "The sort point is nullptr." << endl;
  }else sort_ptr->detail(cout);
}

void reset(){
  if(!is_init) delete []num_seq;
  else is_init = false;

  seq_len = disorder_seq.size();
  num_seq = new double[seq_len];
  size_t i = 0;
  for(auto in: disorder_seq) num_seq[i++] = in;

  release();
}