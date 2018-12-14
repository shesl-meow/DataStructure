#include "Display.h"
#include <cassert>
using namespace std;

template<class T>
void show(std::list<T> lst){
    for(auto i: lst) cout << i << ' ';
}

int main(){
    Display::CircuitBoard cb;
    cb.interactive_init();

    auto ptl = cb.potential_lines();
	if(ptl.size() == 0){
		cout << "You can't get any conduction row with provided laser size." << endl;
		return 1;
	}
    cout << endl << "Potential lines:"; show(ptl); cout << endl;

    auto mode = cb.mode_data(ptl);
    cout << "Mode:"; show(mode); cout << endl;
    
    std::list<bool> laser;
    for(auto it: mode) laser.push_back(!it);
    cout << "Laser:"; show(laser); cout << endl;

    cout << string(cb);
    cout << string(cb.get_column_size(), '|') << endl;
    for(auto i: laser) cout << i;
    cout << endl << string(cb.get_column_size(), '|');
    cb.emit_laser(laser);
    cout << std::string(cb);
    cout << "Conduct rows: " << cb.conduct_rows();
    return 0;
}


