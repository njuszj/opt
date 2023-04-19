# include "./include/common.h"
# include "./opt/Objective.h"
# include "./opt/Variable.h"
# include "./opt/Optimization.h"

int main(){
    LinearIntegerObjective obj(vector<int>({3,4,5}));
    LinearIntegerConstraint con(vector<int>({2,3,4}), 100);
    VariableRange<int> vr(Variable<int>({1, 2, 3}), Variable<int>({100, 200, 300}));
    TraversalSearch opt(obj, con, vr);
    opt.optimize();
}