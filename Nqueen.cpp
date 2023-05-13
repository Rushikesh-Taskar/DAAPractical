#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> ans;
class Solution
{
public:
    bool possible(int col, int row, int n, vector<string> &board)
    {
        // we are moving from left to right so therefore we need to check only 3 direction
        /*

            \
             \
         ---- @ q position in row and direction of checking
             /
            /
        */

        // 1st pos
        int currow = row;
        int curcol = col;
        while (currow >= 0 && curcol >= 0)
        {
            if (board[currow][curcol] == 'Q') // if any other queen exists
            {
                return false;
            }
            currow--;
            curcol--;
        }

        // 2nd pos
        currow = row;
        curcol = col;
        while (curcol >= 0)
        {
            if (board[currow][curcol] == 'Q') // if any other queen exists
            {
                return false;
            }
            curcol--;
        }

        // 3rd pos
        currow = row;
        curcol = col;
        while (currow < n && curcol >= 0)
        {
            if (board[currow][curcol] == 'Q') // if any other queen exists
            {
                return false;
            }
            currow++;
            curcol--;
        }

        return true;
    }
    void solve(int col, vector<string> &board, int n)
    {
        if (col == n)
        {
            ans.push_back(board);
            return;
        }

        // in each column check each row by row
        for (int row = 0; row < n; row++)
        {
            if (possible(col, row, n, board)) // if possible to place at perticular row position then change . to Q and call function for next column and while backtracking again convert Q to . i.e empty
            {
                board[row][col] = 'Q';
                solve(col + 1, board, n);
                board[row][col] = '.'; // backtracking
            }
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        string s(n, '.');           // empty string
        vector<string> board(n, s); // row by row initially all are empty

        // check column by column start from 0th column
        solve(0, board, n);

        return ans;
    }
};

int main()
{
    int n;
    cout << "enter size of n " << endl;
    cin >> n;
    Solution s1;
    s1.solveNQueens(n);
    for (auto it : ans)
    {
        cout << "-----------------" << endl;
        for (auto s : it)
        {
            cout << s << endl;
        }
        cout << "-----------------" << endl;
    }
    return 0;
}
