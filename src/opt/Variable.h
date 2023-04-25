# ifndef VARIABLE_H
# define VARIABLE_H

# include "../include/common.h"
# include "../include/exceptions.h"

template<typename T>
class Variable : public vector<T>{
public:
    using vector<T>::vector;
    Variable operator+(const Variable& var){
        Variable new_var;
        if(var.size() != this->size()){
            throw LengthNoMatch();
        }
        for(int i=0; i<this->size(); i++){
            new_var[i] = var[i] + (*this)[i];
        }
        return new_var;
    }
    Variable operator-(const Variable& var){
        Variable new_var;
        if(var.size() != this->size()){
            throw LengthNoMatch();
        }
        for(int i=0; i<this->size(); i++){
            new_var[i] = (*this)[i] - var[i];
        }
        return new_var;
    }

    int size() {
        return vector<T>::size();
    }
};

template<typename T>
class VariableRange {
    Variable<T>  m_upper_bound;
    Variable<T>  m_lower_bound;
    Variable<T>  m_interval;
    int          m_size;
public:
    VariableRange(Variable<T>&& lower_bound, Variable<T>&& upper_bound) {
        if(lower_bound.size() == upper_bound.size()) {
            m_upper_bound = move(upper_bound);
            m_lower_bound = move(lower_bound);
            m_size = m_lower_bound.size();
            m_interval.resize(m_size);
            for(int i=0; i<m_size; ++i){
                m_interval[i] = m_upper_bound[i] - m_lower_bound[i];
                if(m_interval[i] < 0) logger.ERROR("The value of lower bound is greater than upper bound!");
            }
        }
        else {
            logger.ERROR("The size of lower bound and upper bound don't match!");
        }
    }

    pair<T, T> operator[](int idx){
        return make_pair(m_lower_bound[idx], m_upper_bound[idx]);
    }

    Variable<T> lower_bound() const{
        return m_lower_bound;
    }

    Variable<T> upper_bound() const{
        return m_upper_bound;
    }

    T upper_bound_at(int idx) const {
        return m_upper_bound[idx];
    }

    T lower_bound_at(int idx) const {
        return m_lower_bound[idx];
    }

    Variable<T> interval() const{
        return m_interval;
    }
    
    int size() {
        return m_size;
    }
};

# endif