# include "common.h"
# include <type_traits>

template<typename T>
bool print(T x){
    // 返回值指示是否结尾换行
    cout << x;
    return false;
}

template<typename T>
bool print(vector<T>& vec){
    bool is_basic_type = std::is_same<T, int>::value || 
                        std::is_same<T, float>::value || 
                        std::is_same<T, double>::value || 
                        std::is_same<T, char>::value || 
                        std::is_same<T, bool>::value;
    bool is_string = std::is_same<T, string>::value;
    for(T& ele : vec) {
        print(ele);
        if(is_basic_type) cout << " ";
        else if(is_string) cout << endl;
    }
    if(is_basic_type) {
        cout << endl;
        return true;
    }
    else if(is_string){
        return true;
    }
    else {
        return false;
    }
}

template<typename T1, typename T2>
void print(map<T1, T2>& m){
    for(auto& ele : m){
        print(ele.first);
        cout << ": ";
        bool new_line_flag = print(ele.second);
        if(!new_line_flag) cout << endl;
    }
}