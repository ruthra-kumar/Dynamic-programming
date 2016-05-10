#include <iostream>
#include <queue>
#include <initializer_list>
#include <functional>
#define SIZE 9
#define UNDEFINED 0
using namespace std;
struct Board{
    short brd[SIZE][SIZE];

    Board(){
        for(int i=0;i<SIZE;++i) for(int j=0;j<SIZE;j++) brd[i][j] = UNDEFINED;
    }

    Board(initializer_list<initializer_list<short>> s){
        short row,col;
        row = col = 0;
        for(auto &x:s){
            col = 0;
            for(auto &y:x){
                brd[row][col] = y;
                col++;
            }
            row++;
        }
    }

    //Utility function to print board
    void print_brd(){
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j){
                cout<<brd[i][j]<<" ";
            }
            cout<<'\n';
        }
        cout<<'\n';
    }

    bool operator== (const Board &b){
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;j++){
                if(brd[i][j] != b[i][j]) return false;
            }
        }
        return true;
    }

    typedef short array_type[SIZE];

    array_type& operator[](size_t pos){
        return brd[pos];
    }

    const array_type& operator[] (size_t pos) const {
        return brd[pos];
    }
};

//returns true if value has multiple copies in row
bool inrow(Board &b,int row,int col){

    for(int i=0;(i<SIZE) && (i!=col);i++){
        if(b[row][i] == b[row][col]) return true;
    }
    return false;
}

//returns true if value has multiple copies in column
short incolumn(Board &b,int row,int col){

    for(int i=0;(i<SIZE) && (i!=row);++i){
        if(b[i][col] == b[row][col]) return true;
    }
    return false;
}

//returns true if value has multiple copies in 3x3 box
short inbox(Board &b,int row,int col){
    for(int i=(row-row%3);(i<(row-row%3)+SIZE/3) && (i != row);++i){
        for(int j = (col-col%3) ;(j<(col-col%3)+SIZE/3) && (j != col);++j){
            if(b[i][j] == b[row][col]) return true;
        }
    }
    return false;
}

//returns true if candidate can possibly lead to solutio
//checks to see if board is valid
bool reject(Board &b){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if( (b.brd[i][j] != UNDEFINED) ){
                if( inrow(b,i,j)    ||                  //if duplicate in row
                    incolumn(b,i,j) ||                  //if duplicate in col
                    inbox(b,i,j)                        //if duplicate in box
                  ){
                    return false;
                }
            }
        }
    }
    return true;
}

//bool check if all empty spaces are filled and
//that the sudoku is solved
bool accept(Board &b){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if( (b.brd[i][j] == UNDEFINED)  ||                      //all places have values
                inrow(b,i,j)                ||                      //no duplicate in row
                incolumn(b,i,j)             ||                      //no duplicate in col
                inbox(b,i,j)                                        //no duplicate in box

                ){
                return false;
            }
        }
    }
    return true;
}

//Generates all next candidates and returns a queue of candidates
queue<Board> next(Board &b){
    queue<Board> PossibleCandidates;

    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if(b.brd[i][j] == UNDEFINED){
                for(int val = 1; val <= SIZE ; val++){
                    Board new_candidate = b;
                    new_candidate[i][j] = val;
                    if(reject(new_candidate))
                        PossibleCandidates.push(new_candidate);
                }
                //if the code runs longer than expexted then
                //put a return statement here
                return PossibleCandidates;
            }
        }
    }

    return PossibleCandidates;
}

void Backtrack(Board &root,int &Sol){
    if(!reject(root)) return;
    if(accept(root)){
        root.print_brd();
        Sol++;
        return;
    }

    queue<Board> Candidates = next(root);
    while(!Candidates.empty()){
        Backtrack(Candidates.front(),Sol);
        Candidates.pop();
    }
}

int main(int argc,char *argv[]){
    /*

    Board Start{    {1,2,3,4,5,6,7,8,9},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
                };

    */
    Board Start{    {5,3,0,0,7,0,0,0,0},
                    {6,0,0,1,9,5,0,0,0},
                    {0,9,8,0,0,0,0,6,0},
                    {8,0,0,0,6,0,0,0,3},
                    {4,0,0,8,0,3,0,0,1},
                    {7,0,0,0,2,0,0,0,6},
                    {0,6,0,0,0,0,2,8,0},
                    {0,0,0,4,1,9,0,0,5},
                    {0,0,0,0,8,0,0,7,9},
                };
    /*
    final State that we want
    Board Final{
        {5,3,4,6,7,8,9,1,2},
        {6,7,2,1,9,5,3,4,8},
        {1,9,8,3,4,2,5,6,7},
        {8,5,9,7,6,1,4,2,3},
        {4,2,6,8,5,3,7,9,1},
        {7,1,3,9,2,4,8,5,6},
        {9,6,1,5,3,7,2,8,4},
        {2,8,7,4,1,9,6,3,5},
        {3,4,5,2,8,6,1,7,9},
    };
    */
    int solutions = 0;
    //If you want to the soutions call the print_brd() function
    Backtrack(Start,solutions);
    cout<<solutions<<" different solutions";
    return 0;
}
