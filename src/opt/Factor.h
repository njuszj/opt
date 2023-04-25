# ifndef FACTOR_H
# define FACTOR_H
# include "../include/common.h"

class Factor : public vector<value_t> {
public:
    using vector<value_t>::vector;
    int size() {
        return vector<value_t>::size();
    }
};

# endif