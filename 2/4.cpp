// Sudoku

#include <vector>
using namespace std;

/*
Идея: Предположение индукции: board, который пришел - корректен.
Идем по доске, находим первую пустую ячейку, пытаемся ее брутфорсить
так, чтоб в строке, столбце и квадрате, в которых она содержится, все было ок.
По предположению индукции этого достаточно. Если значение, найденное брутфорсом -
корректно, то пробуем рекурсивно запуститься или говорим об удачном завершении.
 */


class Solution {
public:
    static void solveSudoku(vector<vector<char>>& board) {
        solveSudoku(board, 0, 0);
    }

    static bool solveSudoku(vector<vector<char>>& board, int x, int y) {

        for (size_t i = x; i < 9; ++i) {
            for(size_t j = y; j < 9; ++j) {
                if (board[i][j] == '.') {
                    for(char val = '1'; val <= '9'; ++val) {
                        board[i][j] = val;

                        if (isCorrect(board, i, j)) {
                            int x_next = j == 8 ? i + 1 : i;
                            int y_next = j == 8 ? 0 : j + 1;
                            if ((i == 8 && j == 8) || solveSudoku(board, x_next, y_next)) {
                                return true;
                            }
                        }
                        board[i][j] = '.';
                    }
                    return false;

                }
            }
            y = 0;
        }
        return true;
    }


    static bool isCorrect(vector<vector<char>>& board, int x, int y) {
        for (int i = 0; i < 9; ++i) {
            if (y != i && board[x][i] == board[x][y]) {
                return false;
            }
            if (x != i && board[i][y] == board[x][y]) {
                return false;
            }
        }
        for (int i = x - x % 3; i < x - x % 3 + 3; ++i) {
            for(int j = y - y % 3; j < y - y % 3 + 3; ++j) {
                if (x != i && y != j && board[x][y] == board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};