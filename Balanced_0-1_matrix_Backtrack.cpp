/*
Balanced 0-1 matrix using dynamic programming

*/
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


//returns true if candidate is a solution
bool accept(const _mat &a){
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

//returns false if candidate cannot possibly lead to a solution
bool reject(const _mat &a){
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


//returns list of all next candidates
queue<_mat> next(const _mat &a){
    queue<_mat> l;
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if(a[i][j] == 0){
                _mat tmp = a;
                tmp[i][j] = 1;
                l.push(tmp);
            }
        }
    }
    return l;
}

//main backtrack function works recursively
void Bt(_mat &root,unordered_set<_mat> &Uq_cp){

    if(!reject(root)) return;

    if(accept(root)) Uq_cp.insert(root);

    queue<_mat> candidates = next(root);

    while(!candidates.empty()){
        Bt(candidates.front(),Uq_cp);
        candidates.pop();
    }
}

int main(int argc,char *argv[]){

    _mat Start;
    unordered_set<_mat> Unique_copy;
    Bt(Start,Unique_copy);

    for(auto x:Unique_copy){
        x.print_array();
    }

    return 0;
}
