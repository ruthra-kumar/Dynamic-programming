//Dynamic Programming - elementary example

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
using namespace std;

struct Largest{

    //Store the longest sequence length in here
    int Val=0;
    void operator()(const int &a){
        if(a>Val) Val=a;
    }
};

int main(int argc,char *argv[]){

    //Sequence to check
    vector<int> sequence{5,3,4,8,6,7,10,35,33,12,54,65,87,98,978};
    //Initializing States
    vector<int> states(sequence.size(),1);

    //loop through states
    for(unsigned int i=1;i<states.size();++i){

        //if current index is large than previous index record the longest length
        if(sequence[i-1]<=sequence[i]){
            states[i] = states[i-1]+1;
        }
        else{
            states[i] = states[i-1];
        }
    }

    Largest l = for_each(states.begin(),states.end(),Largest());
    cout<<l.Val<<'\n';

    return 0;
}
