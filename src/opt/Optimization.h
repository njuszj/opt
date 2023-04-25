# ifndef OPTIMIZATION_H
# define OPTIMIZATION_H

# include "Objective.h"
# include "Constraint.h"
# include "Variable.h"
# include "Factor.h"
# include "../include/exceptions.h"
# include "../include/printer.h"

template<typename T>
class OptBase{
protected:
    // 所有优化类的基类
    Objective<T>&  m_objective;                          // 优化目标
    VariableRange<T>& m_range;                           // 变量范围
    ConstraintVector<T>  m_constraints;                  // 约束条件
    Variable<T> m_best_pos;                              // 最佳位置
    Variable<T> m_iter_var;                              // 迭代用变量
    Variable<T> m_iter_upper_bound;                      // 变量上界
    Variable<T> m_iter_lower_bound;                      // 变量下界
    value_t m_min;                                       // 最佳优化值
    bool m_has_next=true;                                // 是否有没有检查过的值
    bool m_start_flag = false;
public:
    OptBase(Objective<T>& objective, VariableRange<T>& range) : m_objective(objective), m_range(range){
        m_iter_var         = m_range.lower_bound();
        m_iter_upper_bound = m_range.upper_bound();
        m_iter_lower_bound = m_range.lower_bound();
        m_min = objective.calculate(m_iter_lower_bound);   // 预先计算最小值
        m_best_pos = m_iter_lower_bound;
    }

    value_t evaluate(){
        Variable<T>& x = m_iter_var;
        value_t res = m_objective.calculate(x);
        logger.INFO("Start to evaluate the point.");
        print(x, res);
        if(res < m_min){
            logger.INFO("The optimal point is updated.");
            m_min = res;
            m_best_pos = x;
        }
        return res;
    }

    virtual bool probe() = 0;

    void optimize(int max_step=1e9){
        int cnt = 0;
        while(probe() && cnt < max_step){
            evaluate();
            cnt++;
        }
    }

    bool check_valid(Variable<T>& x){
        for(shared_ptr<Constraint<T>> iter : m_constraints){
            if(!((iter.get())->check(x))) return false;
        }
        return true;
    }

    Variable<T> currBestPoint(){
        return m_best_pos;
    }

    value_t currBestValue(){
        return m_min;
    }

    void addConstraint(shared_ptr<Constraint<T>> con) {
        m_constraints.push_back(con);
    }

    ~OptBase(){}
};


class LinearIntegerOpt : public OptBase<int> {
    // 线性整数优化问题
public:
    LinearIntegerOpt(LinearIntegerObjective& objective, VariableRange<int>& range) : OptBase<int>(objective, range){}
};


class TraversalSearch : public LinearIntegerOpt {
public:
    // 针对线性整数规划问题进行枚举法暴力搜索
    TraversalSearch(LinearIntegerObjective& objective, VariableRange<int>& range) : LinearIntegerOpt(objective, range){}

    bool probe() override {
        if(!m_has_next) return false;
        logger.DEBUG("Start to probe point.");
        if(!m_start_flag) {
            m_start_flag = true;
            return true;
        }
        bool can_find = false;
        while(1){
            if(m_iter_var[0] < m_range.upper_bound_at(0)){
                m_iter_var[0]++;
                if (check_valid(m_iter_var)) {
                    can_find = true;
                    break;
                }
            }
            else {
                m_iter_var[0] = m_range.lower_bound_at(0);
                int pos_idx = 0;
                for(int i=1; i<m_range.size(); i++){
                    if(m_iter_var[i] == m_range.upper_bound_at(i)) {
                        m_iter_var[i] = m_range.lower_bound_at(i);
                    }
                    else {
                        m_iter_var[i]++;
                        pos_idx = i;
                        break;
                    }
                }
                if(!pos_idx) break;
            }
        }
        if(!can_find) m_has_next = false;
        return can_find;
    }
};

# endif