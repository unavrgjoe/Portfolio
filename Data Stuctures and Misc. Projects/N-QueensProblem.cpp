#include <iostream>
#include <vector>
using namespace std;

//N-Queens Problem
class NQueens{
private:
    int size;
    vector<vector<string>> solutions;
    vector<string> board;
    void initializeBoard(int n){
        size = n;
        string row(n, '_');
        for(int i = 0; i < n; i++){
            board.push_back(row);
        }
    }
    bool isSafe(int row, int col){
        //Check to make sure no queens in column
        for(int i = 0; i < col; i++){
            if(board[row][i] == 'Q'){
                return false;
            }

        }
        //check diagonal starting in top left and working down
        for(int i = row, j = col; i >= 0 && j >= 0; i--, j--){
            if(board[i][j] == 'Q'){
                return false;
            }

        }
        //check other diagonal
        for(int i = row, j = col; i >= 0 && j >= 0; i++, j--){
            if(board[i][j] == 'Q'){
                return false;
            }

        }

        return true;
    }

    void solveNQ(int col){
        //if all queens are placed on board a solution if formed
        if(col >= size){
            solutions.push_back(board);
            return;
            //Not all queens present on board, use recursion with backtracking to determine if solution can be found
        }else{
            for(int i = 0; i < size; i++){
                if(isSafe(i, col) == true){ //safe to place?
                    board[i][col] = 'Q';

                    //recusion to place more queens
                    solveNQ(col+1);
                    //Backtracking
                    board[i][col] = '_';
                }
            }
        }
    }
public:
    //public function user can call to sue the function
    void solveNQueens(int n)   {
        initializeBoard(n);
        solveNQ(0);
        for(auto &solution : solutions){
            for(auto &row : solution){
                cout << row << endl;

            }
            cout << "***********************************************" << endl;
        }
    }
};

int main(){
    NQueens NQ;
    NQ.solveNQueens(4);
}