# ifndef OBJECTIVE_H
# define OBJECTIVE_H

#include "../include/common.h"
#include "Variable.h"
#include "Factor.h"

template<typename T>
class Objective{
protected:
    Factor m_factors;
    int m_size;
public:
    virtual value_t calculate(Variable<T>& x) {return 0;};
};

class LinearIntegerObjective : public Objective<int> {
    // 线性整数优化目标
public:
    LinearIntegerObjective(Factor&& factors){
        m_size = factors.size();
        m_factors = move(factors);
    }

    value_t calculate(Variable<int>& x) {
        if(x.size() != int(m_factors.size())){
            logger.ERROR("The size of variable and factors don't match!");
            return 0;
        }
        value_t res = 0;
        for(int i=0; i<m_size; i++){
            res += m_factors[i] * x[i];
        }
        return res;
    }
};

# endif