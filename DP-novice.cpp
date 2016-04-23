//Dynamic Programming - novice example

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
using namespace std;
int main(int argc,char *argv[]){
    vector<int> coins{1,3,5};

    //all states set to infinity - represented by '100'
    vector<int> states(12,100);
    states[0] = 0;
    int sum=11;
    //for all states or sums in this case 1-11
    //represented by for loop
    for(int i=1;i<=sum;++i){

        //for each state get all coins that is
        //of lower or equal value to sum
        for(auto x:coins){

            //find the (state-coin_value) state and add one it
            if(x <= i && (states.at(i-x)+1<states.at(i))){
                states[i] = states.at(i-x)+1;
            }
        }
    }
    cout<<states.at(sum);

    return 0;
}
