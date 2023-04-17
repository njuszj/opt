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
        logger.INFO("Evaluate the point");
        if(res < m_min){
            logger.INFO("The optimal point is updated.");
            m_min = res;
            m_best_pos = x;
        }
        return res;
    }

    virtual bool probe(){
        // 探测函数，修改m_iter_val, 返回是否还有下一个点
        return false;
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


class TraversalSearch : public LinearIntegerOpt {
protected:
    int m_idx = 0;
    bool m_start_flag = false;
public:
    // 针对线性整数规划问题进行枚举法暴力搜索
    TraversalSearch(LinearIntegerObjective& objective, LinearIntegerConstraint& constraint, VariableRange<int>& range) : LinearIntegerOpt(objective, constraint, range){
        m_iter_var = m_range.lower_bound();
    }
    bool probe() override {
        logger.DEBUG((boost::format("Probe start at position %1%") % m_idx).str());
        if(m_idx == m_range.size()) return false;
        if(!m_start_flag) {
            m_start_flag = true;
            return true;
        }
        if(m_iter_var[m_idx]+1 <= m_range[m_idx].second) {
            m_iter_var[m_idx]++;
            return true;
        }
        else {
            m_idx++;
            return probe();
        }
    }
};