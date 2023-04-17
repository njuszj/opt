# include "common.h"

template<typename T>
void print(T x){
    cout << x;
}

template<typename T>
void print(vector<T>& vec){
    for(T& ele : vec) {
        print(ele);
        cout << " ";
    }
    cout << endl;
}

template<typename T1, typename T2>
void print(map<T1, T2>& m){
    for(auto& ele : m){
        print(ele.first);
        cout << ": ";
        print(ele.second);
        cout << "endl";
    }
}