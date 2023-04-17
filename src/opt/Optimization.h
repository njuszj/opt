# include "Objective.h"
# include "Constraint.h"
# include "Variable.h"

template<typename T>
class OptBase{
protected:
    // 所有优化类的基类
    VariableRange<T>& m_range;                 // 变量范围
    AbstractObjective<T>& m_objective;         // 优化目标
    AbstractConstraint<T>& m_constraint;       // 约束条件
    Variable<T> m_best_pos;                    // 最佳位置
    Variable<T> m_iter_var;                    // 迭代用变量
    double m_min;                              // 最佳优化值
public:
    OptBase(AbstractObjective<T>& objective, AbstractConstraint<T>& constraint, VariableRange<T>& range) : m_objective(objective), m_constraint(constraint), m_range(range){}

    double evaluate(Variable<T>& x){
        double res = m_objective.calculate(x);
        if(res < m_min){
            m_min = res;
            m_best_pos = x;
        }
        return res;
    }

    virtual Variable<T>& probe(){
        // 探测函数，定义寻找下一个要evaluate的点的规则
        return m_iter_var;
    }

    void optimize(){
        while(1){
            Variable<T>& var = probe();
            if(!var) break;
            evaluate(var);
        }
    }
    ~OptBase(){}
};

class LinearIntegerOpt : public OptBase<int> {
    // 线性整数优化问题
public:
    LinearIntegerOpt(LinearIntegerObjective& objective, LinearIntegerConstraint& constraint, VariableRange<int>& range) : OptBase<int>(objective, constraint, range){}
};


class EnumSearchOpt : public LinearIntegerOpt {
protected:
public:
    // 针对线性整数规划问题进行枚举法暴力搜索
    EnumSearchOpt(LinearIntegerObjective& objective, LinearIntegerConstraint& constraint, VariableRange<int>& range) : LinearIntegerOpt(objective, constraint, range){
        m_iter_var = m_range.lower_bound();
        
    }
    Variable<int>& probe() override {
        return m_iter_var;
    }
};