# include "./include/common.h"
# include "./include/printer.h"
# include "./opt/Objective.h"
# include "./opt/Variable.h"
# include "./opt/Optimization.h"


int main(){
    LinearIntegerObjective obj(vector<int>({3, 4, 5, -1, -3, -4, 6, 7, 8}));
    LinearIntegerConstraint con(vector<int>({2,3,4,5,3,4,4,9,2}), 100);
    VariableRange<int> vr(Variable<int>({0, 0, 0, 0, 0, 0, 0, 0, 0}), Variable<int>({2, 2, 2, 2, 2, 2, 2, 2, 2}));
    TraversalSearch opt(obj, con, vr);
    opt.optimize();
    logger.INFO("Optimization has done!");
    print(opt.currBestPoint());
    cout << opt.currBestValue() << endl;
}