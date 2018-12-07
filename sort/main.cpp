#include "Header.h"
#include <iostream>

int main(){
    int a[] = {1, 10, 9, 8, 4};
    std::cout << Sort::BubbleSort<int>(a, 5);

    int b[] = {4, 6, 10, 0, 21, 5};
    std::cout << Sort::SelectionSort<int>(b, 6);
    return 0;
}