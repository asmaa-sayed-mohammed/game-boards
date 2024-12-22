#include "BoardGame_Classes.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;



template <typename T>
class PyramicBoard : public Board<T> {
public:
    PyramicBoard() {
        this->rows = 3;
        this->columns = 5;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns]();
        }
    }

    ~PyramicBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != T()) {
            return false;  // Illegal move if out of bounds or already occupied
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void display_board() override {
        cout << "------------------------"<<endl;
        cout << "    0   1   2   3   4" << endl;
        for (int i = 0; i < this->rows; ++i) {
            cout << i << "   ";
            for (int j = 0; j < this->columns; ++j) {
                if (i == 0 && (j < 2 || j > 2)) {
                    cout << "    ";
                } else if (i == 1 && (j < 1 || j > 3)) {
                    cout << "    ";
                } else {
                    if (this->board[i][j] == T()) {
                        cout << "|   ";
                    } else {
                        cout << this->board[i][j] << "   ";
                    }
                }
            }
            cout << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns - 2; ++j) {
                if (this->board[i][j] != T() && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) {
                    return true;
                }
            }
        }

        for (int i = 0; i < this->rows - 2; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j]) {
                    return true;
                }
            }
        }

        for (int i = 0; i < this->rows - 2; ++i) {
            for (int j = 0; j < this->columns - 2; ++j) {
                if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2]) {
                    return true;
                }
            }
        }

        for (int i = 0; i < this->rows - 2; ++i) {
            for (int j = 2; j < this->columns; ++j) {
                if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j - 1] && this->board[i][j] == this->board[i + 2][j - 2]) {
                    return true;
                }
            }
        }

        return false;

//        for (int i = 0; i < this->rows; i++) {
//            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
//                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
//                return true;
//            }
//        }
//
//        // Check diagonals
//        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
//            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
//            return true;
//        }
//
//        return false;


    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << ", Enter your move (row and column separated by spaces ): \n";
        cin >> x >> y;
    }


};

template <typename T>
class Random : public RandomPlayer<T> {
    public:
    Random(T symbol) : RandomPlayer<T>(symbol) {}
    void getmove(int &x, int &y) override{
        x = rand() % 3;
        y = rand() % 5;

    }

};
