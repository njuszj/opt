# ifndef CONSTRAINT_H
# define CONSTRAINT_H

# include <memory>

#include "../include/common.h"
#include "Variable.h"
#include "Factor.h"

template<typename T>
class Constraint{
    // 所有约束条件的抽象基类
public:
    virtual bool check(Variable<T>& x) { return true; }
};

template<typename T>
using ConstraintVector = vector<std::shared_ptr<Constraint<T>>>;



template<typename T>
class LinearConstraint : public Constraint<T> {
protected:
    Factor m_factors;
    value_t m_target;
public:
    LinearConstraint (const Factor& factors, value_t target) {
        m_factors = move(factors);
        m_target = target;
    }
    virtual bool check(Variable<T>& x) {
        if(x.size() != m_factors.size()) return false;
            value_t res = 0;
            for(int i=0; i<m_factors.size(); i++){
                res += m_factors[i] * x[i];
                if(res > m_target) return false;
            }
            return true;
    };
};


class LinearIntegerConstraint : public LinearConstraint<int> {
    // 线性整数约束
public:
    LinearIntegerConstraint(const Factor& factors, value_t target) : LinearConstraint<int>(factors, target){}
};

# endif