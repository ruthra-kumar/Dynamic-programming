#include <iostream>
#include <vector>
#include <map>
using namespace std;
long long cnt=0;
//Bottom-Up approach
long long Bottom_up(int n){
    //sub-problems
    vector<long long> states(n,1);

    for(int i=2;i<n;++i){
        states[i] = states[i-1]+states[i-2];
    }
    return states[n-1];
}

//Naive approach
//makes a lot of recursive calls - Fib(0) and Fib(1)
long long Fib(int n){
    if(n<=1) return n;
    cnt++;
    return Fib(n-1)+Fib(n-2);
}

//naive approach with associative array
//Reduces recursive call and access data from associative array
long long fib(int n,map<long long,long long> &_m){
    if(_m.find(n) == std::end(_m)){
        cnt++;
        _m[n] = fib((n-1),_m) + fib((n-2),_m);
    }
    return _m.at(n);
}

int main(int argc,char *argv[]){
    //associative array to store calculated values
    map<long long,long long> _map;
    _map[0] = 0;
    _map[1] = 1;

    int val;
    std::cin>>val;
    //cout<<'\n'<<Bottom_up(val);
    //cout<<'\n'<<Fib(val);
    cout<<'\n'<<fib(val,_map);
    cout<<'\n'<<cnt;
    return 0;
}
