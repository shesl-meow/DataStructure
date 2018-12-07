#include "PseudoShell.h"
#include <iostream>

int main(){
    int a[] = {1, 10, 9, 8, 4};
    Sort::BubbleSort<int> s_obj(a, 5);
    std::cout << s_obj;

    int b[] = {4, 6, 10, 0, 21, 5};
    std::cout << Sort::SelectionSort<int>(b, 6);

    Sort::AbstractSort<int>* sort_p;
    int c[] = {100, 60, 4, 20, 1, 58, 91, 17};
    sort_p = new Sort::InsertSort<int>(c, 8);
    sort_p->display(std::cout);
    delete []sort_p;

    int d[] = {100, 60, 72, 20, 1, 58, 91, 17,
               105, 55, 93, 72, 4, 28, 19, 34};
    std::cout << Sort::ShellSort<int>(d, 16, true, [](uint a){ return 2*a + 1; });

    int e[] = {12, 64, 91, 43, 6};
    std::cout << Sort::MergeSort<int>(e, 5);
    
    PseudoShell();
    return 0;
}