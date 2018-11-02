#include "sparse-matrix.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

template<class T>
T SparseMatrix<T>::get(unsigned int row, unsigned int column)const
{
    if(row >= this->row_size || column >= this->column_size)
        throw std::out_of_range("recived argument out of matrix range.");
    for(auto it = this->matrix.begin(); it != this->matrix.end(); ++it)
    {
        if(it->number < column) continue;
        else if(it->number == column)
        {
            for(auto jt = it->data.begin(); jt != it->data.end(); ++jt)
            {
                if(jt->number < row) continue;
                else if(jt->number == row) return jt->data;
                else if(jt->number > row) break;
            }
            break;
        }
        else if(it->number > column) break;
    }
    return T(0);
}

template<class T>
void SparseMatrix<T>::set(unsigned int row, unsigned int column, T data)
{
    if(row >= this->row_size || column >= this->column_size)
        throw std::out_of_range("recived argument out of matrix range.");
    auto it = this->matrix.begin();
    for(; it != this->matrix.end(); ++it)
    {
        if(it->number < column) continue;
        else if(it->number == column)
        {
            for(auto jt = it->data.begin(); jt != it->data.end(); ++jt)
            {
                if(jt->number < row) continue;
                else if(jt->number == row) jt->data = data;
                else if(jt->number > row)
                    it->data.insert(jt, SparseMatrix<T>::Row{data, row});
                break;
            }
            return;
        }
    }
    std::list< SparseMatrix<T>::Row > new_row{ SparseMatrix<T>::Row{data,row} };
    SparseMatrix<T>::Column new_column{new_row, column};
    this->matrix.insert(it, new_column);
}

template<class T>
SparseMatrix<T>::operator std::string()const
{
    std::stringstream ss;
    for(unsigned int i = 0; i < this->row_size; ++i)
    {
        for(unsigned int j = 0; j < this->column_size; ++j)
            ss << this->get(i,j) << " ";
        ss << std::endl;
    }
    return ss.str();
}
