# include "../include/common.h"

template<typename T>
using Variable = vector<T>;

template<typename T>
class VariableRange {
    vector<T> m_upper_bound;
    vector<T> m_lower_bound;
    int       m_size;
public:
    VariableRange(vector<T>&& lower_bound, vector<T>&& upper_bound) {
        if(lower_bound.size() == upper_bound.size()) {
            m_size = m_lower_bound.size();
            m_upper_bound = move(upper_bound);
            m_lower_bound = move(lower_bound);
        }
        else {
            logger.ERROR("The size of lower bound and upper bound don't match!");
        }
    }

    pair<T, T> operator[](int idx){
        return make_pair(m_lower_bound[idx], m_upper_bound[idx]);
    }

    vector<T>& lower_bound(){
        return m_lower_bound;
    }

    vector<T>& upper_bound(){
        return m_upper_bound;
    }
    
    int size() {
        return m_size;
    }
};
