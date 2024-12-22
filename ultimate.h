#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


template<typename T>
class board1: public Board<T>{
public:
    board1();
    char ** board2;
    int move = 0;
    bool update_board(int x ,int y ,T symbol);
    void display_board();
    void is_win1() ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void fill_related_cells(int groupRow, int groupCol, char symbol);
};

template <typename T>
class ultimate_Player : public Player<T> {
public:
    ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class ultimate_Random_Player : public RandomPlayer<T>{
public:
    ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
class execute20{
public:
    void execute18();
};
////=========================IMPLEMENTATION==============================================

#include <iomanip>
#include <cctype>  // for toupper()

template <typename T>
void board1<T>::fill_related_cells(int groupRow, int groupCol, char symbol) {
    int startRow = groupRow * 3; // Map group row to board row
    int startCol = groupCol * 3; // Map group column to board column

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (this->board[i][j] == 0) { // Only fill empty cells
                this->board[i][j] = symbol;
                this->n_moves++;
            }
        }
    }
}


template <typename T>
board1<T>::board1() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    board2 = new char * [3];
    for (int i = 0; i < 3; ++i) {
        board2[i] = new char [3];
        for (int j = 0; j < 3; ++j) {
            board2[i][j] = 0;
        }

    }
    this->n_moves = 0;
}

template <typename T>
bool board1<T>::update_board(int x, int y, T mark1) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark1 == 0)) {
        if (mark1 == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark1);
        }
        this->is_win1();
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void board1<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                cout << "(" << i << "," << j << ")";
                cout << setw(4) << this->board[i][j] << " |";
            }else {
                cout << setw(4) << this->board[i][j] << "  |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\n| ";
        for (int j = 0; j < 3; j++) {
            if (this->board2[i][j] == 0) {
                cout << "(" << i << "," << j << ")";
                cout << setw(4) << this->board2[i][j] << " |";
            } else {
                cout << setw(4) << this->board2[i][j] << "  |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
void board1<T>::is_win1() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 7; col += 3) {
            if (this->board[row][col] == this->board[row][col + 1] &&
                this->board[row][col + 1] == this->board[row][col + 2] &&
                this->board[row][col] != 0) {
                this->board2[row / 3][col / 3] = this->board[row][col];
                this->fill_related_cells(row/3, col/3, this->board[row][col]);

            }
        }
    }

    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 7; row += 3) {
            if (this->board[row][col] == this->board[row + 1][col] &&
                this->board[row + 1][col] == this->board[row + 2][col] &&
                this->board[row][col] != 0) {
                this->board2[row / 3][col / 3] = this->board[row][col];
                this->fill_related_cells(row/3, col/3, this->board[row][col]);
            }
        }
    }

    if (this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2] &&
        this->board[0][0] != 0) {
        this->board2[0][0] = this->board[0][0];
        this->fill_related_cells(0, 0, this->board[0][0]);
    }

    if (this->board[0][2] == this->board[1][1] &&
        this->board[1][1] == this->board[2][0] &&
        this->board[0][2] != 0) {
        this->board2[0][0] = this->board[0][2];
        this->fill_related_cells(0, 0, this->board[0][2]);
    }

    if (this->board[0][3] == this->board[1][4] &&
        this->board[1][4] == this->board[2][5] &&
        this->board[0][3] != 0) {
        this->board2[0][1] = this->board[0][3];
        this->fill_related_cells(0, 1, this->board[0][3]);
    }

    if (this->board[0][5] == this->board[1][4] &&
        this->board[1][4] == this->board[2][3] &&
        this->board[0][5] != 0) {
        this->board2[0][1] = this->board[0][5];
        this->fill_related_cells(0, 1, this->board[0][5]);
    }

    if (this->board[0][8] == this->board[1][7] &&
        this->board[1][7] == this->board[2][6] &&
        this->board[0][8] != 0) {
        this->board2[0][2] = this->board[0][8];
        this->fill_related_cells(0, 2, this->board[0][8]);
    }

    if (this->board[0][6] == this->board[1][7] &&
        this->board[1][7] == this->board[2][8] &&
        this->board[0][8] != 0) {
        this->board2[0][2] = this->board[0][6];
        this->fill_related_cells(0, 2, this->board[0][6]);
    }

    if (this->board[3][0] == this->board[4][1] &&
        this->board[4][1] == this->board[5][2] &&
        this->board[3][0] != 0) {
        this->board2[1][0] = this->board[3][0];
        this->fill_related_cells(1, 0, this->board[3][0]);
    }

    if (this->board[3][2] == this->board[4][1] &&
        this->board[4][1] == this->board[5][0] &&
        this->board[3][2] != 0) {
        this->board2[1][0] = this->board[3][2];
        this->fill_related_cells(1, 0, this->board[3][2]);
    }

    if (this->board[3][3] == this->board[4][4] &&
        this->board[4][4] == this->board[5][5] &&
        this->board[3][3] != 0) {
        this->board2[1][1] = this->board[3][3];
        this->fill_related_cells(1, 1, this->board[3][3]);
    }

    if (this->board[3][5] == this->board[4][4] &&
        this->board[4][4] == this->board[5][3] &&
        this->board[3][5] != 0) {
        this->board2[1][1] = this->board[3][5];
        this->fill_related_cells(1, 1, this->board[3][5]);
    }

    if (this->board[3][6] == this->board[4][7] &&
        this->board[4][7] == this->board[5][8] &&
        this->board[3][6] != 0) {
        this->board2[1][2] = this->board[3][6];
        this->fill_related_cells(1, 2, this->board[3][6]);
    }

    if (this->board[3][8] == this->board[4][7] &&
        this->board[4][7] == this->board[5][6] &&
        this->board[3][8] != 0) {
        this->board2[1][2] = this->board[3][8];
        this->fill_related_cells(1, 2, this->board[3][8]);
    }

    if (this->board[6][0] == this->board[7][1] &&
        this->board[7][1] == this->board[8][2] &&
        this->board[6][0] != 0) {
        this->board2[2][0] = this->board[6][0];
        this->fill_related_cells(2, 0, this->board[6][0]);
    }

    if (this->board[6][2] == this->board[7][1] &&
        this->board[7][1] == this->board[8][0] &&
        this->board[6][2] != 0) {
        this->board2[2][0] = this->board[6][2];
        this->fill_related_cells(2, 0, this->board[6][2]);
    }

    if (this->board[6][3] == this->board[7][4] &&
        this->board[7][4] == this->board[8][5] &&
        this->board[6][3] != 0) {
        this->board2[2][1] = this->board[6][3];
        this->fill_related_cells(2, 1, this->board[6][3]);
    }

    if (this->board[6][5] == this->board[7][4] &&
        this->board[7][4] == this->board[8][3] &&
        this->board[6][5] != 0) {
        this->board2[2][1] = this->board[6][5];
        this->fill_related_cells(2, 1, this->board[6][5]);
    }

    if (this->board[6][8] == this->board[7][7] &&
        this->board[7][7] == this->board[8][6] &&
        this->board[6][8] != 0) {
        this->board2[2][2] = this->board[6][8];
        this->fill_related_cells(2, 2, this->board[6][8]);
    }

    if (this->board[6][6] == this->board[7][7] &&
        this->board[7][7] == this->board[8][8] &&
        this->board[6][6] != 0) {
        this->board2[2][2] = this->board[6][6];
        this->fill_related_cells(2, 2, this->board[6][6]);
    }
}

template <typename T>
bool board1<T>::is_win(){
    this->is_win1();
    for (int i = 0; i < 3; i++) {
        if ((this->board2[i][0] == this->board2[i][1] && this->board2[i][1] == this->board2[i][2] && this->board2[i][0] != 0) ||
            (this->board2[0][i] == this->board2[1][i] && this->board2[1][i] == this->board2[2][i] && this->board2[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board2[0][0] == this->board2[1][1] && this->board2[1][1] == this->board2[2][2] && this->board2[0][0] != 0) ||
        (this->board2[0][2] == this->board2[1][1] && this->board2[1][1] == this->board2[2][0] && this->board2[0][2] != 0)) {
        return true;
    }

    return false;
}

template <typename T>
ultimate_Player<T>::ultimate_Player(std::string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ultimate_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
ultimate_Random_Player<T>::ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 8
    y = rand() % this->dimension;
}

template <typename T>
bool board1<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool board1<T>::game_is_over() {
    return is_win() || is_draw();
}

void execute20::execute18() {
        int choice;
        Player<char>* players[2];
        board1<char>* B = new board1<char>();
        string playerXName, player2Name;

        cout << "Welcome to FCAI Ultimate X-O Game. :)\n";

        // Set up player 1
        cout << "Enter Player X name: ";
        cin >> playerXName;
        do {
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            if (choice == 1) {
                players[0] = new ultimate_Player<char>(playerXName, 'X');
            } else if (choice == 2) {
                players[0] = new ultimate_Random_Player<char>('X');
            } else {
                cout << "Invalid choice. Please select again.\n";
            }
        } while (choice != 1 && choice != 2);

        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        do {
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            if (choice == 1) {
                players[1] = new ultimate_Player<char>(player2Name, 'O');
            } else if (choice == 2) {
                players[1] = new ultimate_Random_Player<char>('O');
            } else {
                cout << "Invalid choice. Please select again.\n";
            }
        } while (choice != 1 && choice != 2);

        // Create the game manager and run the game
        GameManager<char> x_o_game(B, players);

        // Run the game loop
        x_o_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
}

#endif//ULTIMATE_H
