# ifndef OPTIMIZATION_H
# define OPTIMIZATION_H

# include "Objective.h"
# include "Constraint.h"
# include "Variable.h"
# include "../include/exceptions.h"
# include "../include/printer.h"

template<typename T>
class OptBase{
protected:
    // 所有优化类的基类
    AbstractObjective<T>& m_objective;         // 优化目标
    AbstractConstraint<T>& m_constraint;       // 约束条件
    VariableRange<T>& m_range;                 // 变量范围
    Variable<T> m_best_pos;                    // 最佳位置
    Variable<T> m_iter_var;                    // 迭代用变量
    Variable<T> m_iter_upper_bound;            // 变量上界
    Variable<T> m_iter_lower_bound;            // 变量下界
    double m_min;                              // 最佳优化值
    bool m_has_next=true;                      // 是否有没有检查过的值
    bool m_start_flag = false;
public:
    OptBase(AbstractObjective<T>& objective, AbstractConstraint<T>& constraint, VariableRange<T>& range) : m_objective(objective), m_constraint(constraint), m_range(range){
        m_iter_var         = m_range.lower_bound();
        m_iter_upper_bound = m_range.upper_bound();
        m_iter_lower_bound = m_range.lower_bound();
        m_min = objective.calculate(m_iter_lower_bound);   // 预先计算最小值
    }

    double evaluate(){
        double res = m_objective.calculate(m_iter_var);
        logger.INFO("Start to evaluate the point.");
        print(m_iter_var, res);
        if(res < m_min){
            logger.INFO("The optimal point is updated.");
            m_min = res;
            m_best_pos = m_iter_var;
        }
        return res;
    }

    virtual bool probe() = 0;

    void optimize(){
        while(probe()){
            evaluate();
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
public:
    // 针对线性整数规划问题进行枚举法暴力搜索
    TraversalSearch(LinearIntegerObjective& objective, LinearIntegerConstraint& constraint, VariableRange<int>& range) : LinearIntegerOpt(objective, constraint, range){}

    bool probe() override {
        if(!m_has_next) return false;
        logger.DEBUG("Start to probe point.");
        if(!m_start_flag) {
            m_start_flag = true;
            return true;
        }
        bool can_find = false;
        int pos_idx = 0;
        while(pos_idx <= m_range.size()){
            if(m_iter_var[pos_idx] < m_range.upper_bound(pos_idx)){
                m_iter_var[pos_idx]++;
                if(m_constraint.check(m_iter_var)){
                    can_find = true;
                    break;
                }
            }
            else {
                m_iter_var[pos_idx] = m_iter_lower_bound[pos_idx];
                pos_idx++;
            }
        }
        if(!can_find) m_has_next = false;
        return can_find;
    }
};

# endif