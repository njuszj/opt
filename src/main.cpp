# include "./include/common.h"
# include "./opt/Objective.h"

int main(){
    Variable x;
    x.vals = vector<int>({1,2,4});
    LinearIntegerObjective obj(vector<int>({1,2,3}));
    double r = obj.calculate(x);
}