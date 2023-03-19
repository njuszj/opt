# include "../include/common.h"

// enum VariableType{
//     Discrete,       // 离散
//     Continuous,     // 连续
//     Mixed           // 混合
// };

class VariableInfo { 
    int n_;                                 // 变量的维度
    // VariableType type_;                  // 变量的类型
    vector<pair<int, int>> range_           // 变量的范围
};

class Variable {
    int n_;
public:
    vector<int> vals;
    int size(){
        return n_;
    }
}