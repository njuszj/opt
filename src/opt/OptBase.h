# include "Objective.h"
# include "Constraint.h"
# include "Variable.h"

class OptBase{
    // 所有优化类的基类
    VariableRange& m_range;                 // 变量范围
    AbstractObjective& m_objective;         // 优化目标
    AbstractConstraint& m_constraint;       // 约束条件
    Variable& m_best_pos;                   // 最佳位置
    double m_min;                           // 最佳优化值
public:
    OptBase(AbstractObjective& objective, AbstractConstraint& constraint, VariableRange& range) : m_objective(objective), m_constraint(constraint), m_range(range){
        
    }

    double evaluate(Variable& x){
        double res = m_objective.calculate(x);
        m_min = m_min < res ? m_min : res;
        return res;
    }

    ~OptBase(){

    }
};

class LinearIntegerOpt : public OptBase {
    // 线性整数优化问题
public:
    LinearIntegerOpt(LinearObjective& objective, LinearConstraint& constraint, IntegerVariableRange& range) : OptBase(objective, constraint, range){}
};

class EnumSearch : public LinearIntegerOpt {
    // 枚举法暴力搜索
    EnumSearch(LinearObjective& objective, LinearConstraint& constraint, IntegerVariableRange& range) : LinearIntegerOpt(objective, constraint, range){}
    
};