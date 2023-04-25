# include "./include/common.h"
# include "./include/printer.h"
# include "./opt/Objective.h"
# include "./opt/Variable.h"
# include "./opt/Optimization.h"


int main(){
    logger.setLogLevel(Logger::info);
    LinearIntegerObjective obj(Factor({3, 4, 5, -1, -3, -4, 6, 7, 8}));
    VariableRange<int> vr(Variable<int>({0, 0, 0, 0, 0, 0, 0, 0, 0}), Variable<int>({2, 2, 2, 2, 2, 2, 2, 2, 2}));
    TraversalSearch opt(obj, vr);
    opt.addConstraint(std::make_shared<LinearIntegerConstraint>(Factor({2,3,4,5,3,4,4,9,200}), 100));
    opt.optimize();
    logger.INFO("Optimization has done!");
    cout << endl;
    print(opt.currBestPoint());
    cout << opt.currBestValue() << endl;
}