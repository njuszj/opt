# include "../src/include/printer.h"
# include "../src/include/common.h"

int main(){
    vector<int> a({1,2,3});
    vector<int> b({2,3,4,5});
    vector<vector<int>> c({a, b});
    map<int, vector<int>> m;
    m[1] = a;
    m[2] = b;
    print(m);
}