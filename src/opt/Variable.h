# include "../include/common.h"


class VariableRange {
public:
    int n_;                                         // 变量的维度
    vector<pair<double, double>> range_;            // 变量的范围
};

class IntegerVariableRange : public VariableRange {
public:
    int n_;                                  // 变量的维度
    vector<pair<int, int>> range_;           // 变量的范围
};

class Variable {
public: 
    vector<double> vals;
};

class IntegerVariable : public Variable {
public:
    vector<int> vals;
};

class DoubleVariable : public Variable {
    vector<double> vals;
};
