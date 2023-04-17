#include "../include/common.h"
#include "Variable.h"

template<typename T>
class AbstractObjective{
protected:
    vector<int> m_factors;
    int m_size;
public:
    virtual double calculate(Variable<T>& x) = 0;
};

class LinearIntegerObjective : public AbstractObjective<int> {
    // 线性整数优化目标
public:
    LinearIntegerObjective(vector<int>&& factors){
        m_size = factors.size();
        m_factors = move(factors);
    }

    double calculate(Variable<int>& x) {
        if(x.size() != m_factors.size()){
            logger.ERROR("The size of variable and factors don't match!");
            return 0;
        }
        double res = 0;
        for(int i=0; i<m_size; i++){
            res += m_factors[i] * x[i];
        }
        return res;
    }
};