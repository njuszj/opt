#include "../include/common.h"
#include "Variable.h"

class AbstractConstraint{
    // 所有约束条件的抽象基类
protected:
    vector<int> factors_;
    int n_;
    double target_;
public:
    virtual bool check(Variable& x) = 0;
};

class LinearConstraint : public AbstractConstraint {
public:
    LinearConstraint(vector<int>&& factors, double target){
        factors_ = move(factors);
        n_ = factors.size();
        target_ = target;
    }

    bool check(Variable& x) {
        assert(x.size() == n_);
        double res = 0;
        for(int i=0; i<n_; i++){
            res += factors_[i] * x.vals[i];
        }
        return res < target_;
    }
};