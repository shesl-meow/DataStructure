#include <iostream>
#include <string>
#include <list>
#include "Header.h"
#include "HashString.h"
using namespace std;

bool is_init = true;
bool is_ascend = true;
double* number_sequence;
uint sequence_length = 0;

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
void ExeCommand(string pseudo_command)
{
  switch (hash_(pseudo_command.c_str())) {
    case "help"_hash: help(); break;
    case "assign"_hash: assign(); break;
    case "toggle"_hash: toggle(); break;
    case "bubble"_hash: 
        cout << Sort::BubbleSort<double>(number_sequence, sequence_length, is_ascend); break;
    case "insert"_hash:
        cout << Sort::InsertSort<double>(number_sequence, sequence_length, is_ascend); break;
    case "select"_hash:
        cout << Sort::SelectionSort<double>(number_sequence, sequence_length, is_ascend); break;
    case "merge"_hash:
        cout << Sort::MergeSort<double>(number_sequence, sequence_length, is_ascend); break;
    case "shell"_hash:
        cout << Sort::ShellSort<double>(
          number_sequence, sequence_length, is_ascend, [](uint an){ return 3*an - 1; }); break;
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
    "[toggle]: toggle status between ascend and descend.\n"
    "[bubble]: apply bubble sort on the current sequence.\n"
    "[insert]: apply insert sort on the current sequence.\n"
    "[select]: apply select sort on the current sequence.\n"
    "[merge]: apply merge sort on the current sequence.\n";
  cout << manual;
}

void assign()
{
  cout << "Assign the list waiting to be sorted, any illegal input will end input." << endl;
  double tmp;
  list<double> input_list;
  while(cin >> tmp) input_list.push_front(tmp);
  cin.clear();

  if(!is_init) delete []number_sequence;
  else is_init = false;

  sequence_length = input_list.size();
  number_sequence = new double[sequence_length];
  size_t i = 0;
  for(auto in: input_list) number_sequence[i++] = in;
}