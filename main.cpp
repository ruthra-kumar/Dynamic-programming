#include <iostream>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#define SIZE 4
using namespace std;

struct _mat{
    bool Mat[SIZE][SIZE];

    _mat(){
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j)
                Mat[i][j] = 0;
        }
    }

    void print_array(){
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j){
                cout<<Mat[i][j]<<" ";
            }
            cout<<'\n';
        }
        cout<<'\n';
    }

    // const in suffix is needed for it to work in unordered_set
    bool operator==(const _mat &a) const{
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j){
                if(a[i][j] != Mat[i][j])
                    return false;
            }
        }
        return true;
    }

    // const in suffix is needed for it to work in unordered_set
    bool operator!= (const _mat &a) const{
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j){
                if(a[i][j] != Mat[i][j])
                    return true;
            }
        }
        return false;
    }

    //following two [] operators are oveloaded for [][] operators to work directly in struct object

    typedef bool array_type[SIZE];

    array_type& operator[] (std::size_t pos){
        return Mat[pos];
    }

    const array_type& operator[](std::size_t pos) const{
        return Mat[pos];
    }

};

//Helper function to check balance of board
bool Check_balance(const _mat &a){
    int row,col;
    col=row=0;
    for(int i=0;i<SIZE;){
        for(int j=0;j<SIZE;++j){
            if(a[i][j] == 1) row++;
        }
        if(row == SIZE/2){
            ++i;
            row = 0;
        }
        else return false;
    }

    for(int i=0;i<SIZE;){
        for(int j=0;j<SIZE;++j){
            if(a[j][i] == 1) col++;
        }
        if(col == SIZE/2){
            ++i;
            col = 0;
        }
        else return false;
    }
    return true;
}

//helper function to check if board has gone out of balance
//it essentially finds out whether balance state can be reached
bool Check_Credibility(const _mat &a){
    int row,col;
    row=0;
    for(int i=0;i<SIZE;){
        for(int j=0;j<SIZE;++j){
            if(a[i][j] == 1) row++;
        }
        if(row <= SIZE/2){
            ++i;
            row = 0;
        }
        else return false;
    }
    col = 0;
    for(int i=0;i<SIZE;){
        for(int j=0;j<SIZE;++j){
            if(a[j][i] == 1) col++;
        }
        if(col <= SIZE/2){
            ++i;
            col = 0;
        }
        else return false;
    }
    return true;
}

//custom hash function to handle _mat object
//needed by unordered_set container to create a unique hash
namespace std{
//custom hash inserted into std namespace
    template<> struct hash<_mat>{
        size_t operator()(const _mat &a) const {
            size_t d=1;

            for(int i=0;i<SIZE;++i){
                for(int j=0;j<SIZE;++j){
                    d += (d ^= a[i][j]);
                }
            }
            return d;
        }
    };

}

int main(int argc,char *argv[])
{


    _mat Start;
    //Stores all feasible board configurations
    queue<_mat> lst;
    //unique copies of board positions
    unordered_set<_mat> Unique_copy{Start};
    lst.push(Start);

    for( ; (!lst.empty()) ; ){
        _mat Current_state = lst.front();

        //only prints unique balanced board
        //it considers mirrored board positions as unique as well
        if(Check_balance(Current_state)) Current_state.print_array();

        //generate all possible configurations from current
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j){
                if( Current_state[i][j] == 0){

                    _mat New_State = Current_state;
                    New_State[i][j] = 1;

                    //See if New_state has gone out of balance
                    if(Check_Credibility(New_State)){
                        //If no copy is already present add it to queue
                        //.. and make a copy
                        if(Unique_copy.find(New_State) == end(Unique_copy)){
                            //Add to the queue
                            lst.push(New_State);

                            //Make a unique copy for printing out later
                            Unique_copy.insert(New_State);
                        }
                    }
                }
            }
        }
        lst.pop();
    }
    return 0;
}
