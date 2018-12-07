#pragma once
#include <fstream>
#include <functional>
#include <list>

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
        inline void assign(uint start, uint len, T* data);
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

    template<class T>
    class ShellSort: public AbstractSort<T>{
    private:
        std::function<uint(uint)> forward_f;
        std::list<uint> sequence;

        inline void generate_seq();
    public:
        ShellSort(T* src, uint l, bool ascend = true, 
            std::function<uint(uint)> f = [](uint an){ return 3*an - 1; }):
            AbstractSort<T>(src, l, ascend), forward_f(f) { this->sort(); }
        void sort() override;
    };

    template<class T>
    class MergeSort: public AbstractSort<T>{
    private:
        inline void merge(uint start1, uint len1, uint start2, uint len2);
    public:
        MergeSort(T* src, uint l, bool ascend = true):
            AbstractSort<T>(src, l, ascend) { this->sort(); }
        void sort() override;
    };
}