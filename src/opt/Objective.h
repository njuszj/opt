#include "../include/common.h"
#include "Variable.h"

class AbstractObjective{
protected:
    vector<int> factors_;
    int n_;
    double target_;
public:
    virtual double calculate(Variable& x) = 0;
};

class LinearObjective : public AbstractObjective {
public:
    LinearObjective(vector<int>&& factors){
        factors_ = move(factors);
        n_ = factors.size();
    }

    double calculate(Variable& x) {
        assert(x.vals.size() == n_);
        double res = 0;
        for(int i=0; i<n_; i++){
            res += factors_[i] * x.vals[i];
        }
        return res;
    }
};