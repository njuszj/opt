# include "./include/common.h"
# include "./opt/Objective.h"

int main(){
    Variable<int> x({1,3,4});
    LinearIntegerObjective obj(vector<int>({1,2,3}));
    double r = obj.calculate(x);
}