# include "../src/include/printer.h"
# include "../src/include/common.h"

int main(){
    vector<int> a({1,2,3});
    vector<int> b({2,3,4});
    vector<vector<int>> c({a, b});
    print(c);
}