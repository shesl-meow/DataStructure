#include "Header.h"
#include <iostream>

int main(){
    int a[] = {1, 10, 9, 8, 4};
    std::cout << Sort::BubbleSort<int>(a, 5);

    int b[] = {4, 6, 10, 0, 21, 5};
    std::cout << Sort::SelectionSort<int>(b, 6);

    int c[] = {100, 60, 4, 20, 1, 58, 91, 17};
    std::cout << Sort::InsertSort<int>(c, 8);

    int d[] = {100, 60, 72, 20, 1, 58, 91, 17,
               105, 55, 93, 72, 4, 28, 19, 34};
    std::cout << Sort::ShellSort<int>(d, 16, true, [](uint a){ return 2*a + 1; });

    int e[] = {12, 64, 91, 43, 6};
    std::cout << Sort::MergeSort<int>(e, 5);
    return 0;
}