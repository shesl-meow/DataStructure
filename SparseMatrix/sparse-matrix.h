#include<list>
#include<string>
#include<iostream>

template<class T>
class SparseMatrix{
public:
    SparseMatrix(unsigned int row, unsigned int column): row_size(row), column_size(column){}

    T get(unsigned int row, unsigned int column)const;
    void set(unsigned int row, unsigned int column, T data);
    void display()const{ std::cout << std::string(*this) << std::endl;}

    // convert operator. 定义了将 SparseMatrix 强制类型转化未 string 的方法。
    operator std::string()const;
private:
    struct Row{T data; unsigned int number;}; // 这里的 number 是一个行号
    struct Column{std::list<Row> data; unsigned int number;}; // 这里的 number 是一个列号
    std::list<Column> matrix;

    unsigned int row_size;
    unsigned int column_size;
};
