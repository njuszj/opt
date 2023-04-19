# include "./include/common.h"
# include "./opt/Objective.h"
# include "./opt/Variable.h"
# include "./opt/Optimization.h"

int main(){
    LinearIntegerObjective obj(vector<int>({3,4,5}));
    LinearIntegerConstraint con(vector<int>({2,3,4}), 10);
    VariableRange<int> vr(Variable<int>({1, 2, 3}), Variable<int>({10, 10, 10}));
    TraversalSearch opt(obj, con, vr);
    opt.optimize();
}