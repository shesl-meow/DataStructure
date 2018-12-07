#pragma once
#include <fstream>
#include <iostream> // debug

typedef unsigned int uint;

namespace Sort{
    template<class T>
    class AbstractSort{
    protected:
        T* src_list;
        uint length;
        bool is_ascend;
        bool is_sorted = false;

        inline bool compare(uint index1, uint index2)const;
        inline void swap(uint index1, uint index2);
    public:
        AbstractSort(T* src, uint l, bool ascend = true):
            src_list(src), length(l), is_ascend(ascend) {}
        
        virtual void sort() = 0;
        std::ostream& display(std::ostream& out)const;
    };

    template<class T>
    class BubbleSort: public AbstractSort<T>{
    public:
        BubbleSort(T* src, uint l, bool ascend = true):
            AbstractSort<T>(src, l, ascend) { this->sort(); }
        void sort() override;
    };

    template<class T>
    class SelectionSort: public AbstractSort<T>{
    public:
        SelectionSort(T* src, uint l, bool ascend = true):
            AbstractSort<T>(src, l, ascend) { this->sort(); }
        void sort() override;
    };

    template<class T>
    class InsertSort: public AbstractSort<T>{
    public:
        InsertSort(T* src, uint l, bool ascend = true):
            AbstractSort<T>(src, l, ascend) { this->sort(); }
        void sort() override;
    };
}