#include "../include/common.h"
#include "Variable.h"


template<typename T>
class AbstractConstraint{
    // 所有约束条件的抽象基类
protected:
    vector<T> m_factors;
    int m_size;
    double m_target;
public:
    virtual bool check(Variable<T>& x) = 0;
};


class LinearIntegerConstraint : public AbstractConstraint<int> {
    // 线性整数约束
public:
    LinearIntegerConstraint(vector<int>&& factors, double target){
        m_size = factors.size();
        m_factors = move(factors);
        m_target = target;
    }

    bool check(Variable<int>& x) {
        if(x.size() != m_size) return false;
        double res = 0;
        for(int i=0; i<m_size; i++){
            res += m_factors[i] * x[i];
        }
        return res < m_target;
    }
};