#ifndef four_Rows_H
#define four_Rows_H

#include <iostream>
#include <iomanip>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include "BoardGame_Classes.h"

template <typename T>
class four_row_Board: public Board<T> {
public:
    four_row_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class four_row_player : public Player<T> {
public:
    four_row_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class four_row_Random_Player : public RandomPlayer<T> {
public:
    four_row_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class execute1{
public:
    void execute();
};

// Implementation
using namespace std;

template<typename T>
four_row_Board<T>::four_row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool four_row_Board<T>::update_board(int x, int y, T mark) {
    if (y < 0 || y >= this->columns) {
        cout << "wrong number please insert only numbers from 0 to 6 included 0 and 6\n";
        return false;
    }

    int row = -1; // this mean there is no empty cell in column
    for (int i = this->rows - 1; i >= 0; --i) {
        if (this->board[i][y] == 0) {
            row = i;
            break;
        }
    }

    if (row == -1) {
        cout << "there is no empty cell in this column, please insert another column\n";
        return false;
    }

    if (mark == 0) {
        if (row + 1 < this->rows && this->board[row + 1][y] == 0) {
            return false;
        }
        this->n_moves--;
        this->board[row][y] = 0;
    } else {
        this->n_moves++;
        this->board[row][y] = toupper(mark);
    }

    return true;
}


template <typename T>
void four_row_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                cout << setw(3) << "(" << i << "," << j << ")" << " |";
            } else {
                cout << setw(3) << this->board[i][j] << "  |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool four_row_Board<T>::is_win() {
    // Check columns
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns - 3; ++j) {
            if ((this->board[i][j] != 0) &&
                (this->board[i][j] == this->board[i][j + 1]) &&
                (this->board[i][j] == this->board[i][j + 2]) &&
                (this->board[i][j] == this->board[i][j + 3])) {
                return true;
            }
        }
    }

    // Check rows
    for (int i = 0; i < this->rows - 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if ((this->board[i][j] != 0) &&
                (this->board[i][j] == this->board[i + 1][j]) &&
                (this->board[i][j] == this->board[i + 2][j]) &&
                (this->board[i][j] == this->board[i + 3][j])) {
                return true;
            }
        }
    }

    // Check diagonals (down-right)
    for (int i = 0; i < this->rows - 3; ++i) {
        for (int j = 0; j < this->columns - 3; ++j) {
            if ((this->board[i][j] != 0) &&
                (this->board[i][j] == this->board[i + 1][j + 1]) &&
                (this->board[i][j] == this->board[i + 2][j + 2]) &&
                (this->board[i][j] == this->board[i + 3][j + 3])) {
                return true;
            }
        }
    }

    // Check diagonals (down-left)
    for (int i = 0; i < this->rows - 3; ++i) {
        for (int j = this->columns - 1; j > 2; --j) {
            if ((this->board[i][j] != 0) &&
                (this->board[i][j] == this->board[i + 1][j - 1]) &&
                (this->board[i][j] == this->board[i + 2][j - 2]) &&
                (this->board[i][j] == this->board[i + 3][j - 3])) {
                return true;
            }
        }
    }
    return false;
}


template <typename T>
bool four_row_Board<T>::is_draw() {
    return ((this->n_moves == 42 ) && (!is_win()));
}

template <typename T>
bool four_row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for four_row_player
template <typename T>
four_row_player<T>::four_row_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_row_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your column number (0 or 1): ";
    while (true) {
        string input;
        cin >> input;

        // Validate that the input is exactly one character long and is either '0' or '1'
        if (input.size() == 1) {
            string n;
            n = input.substr(0,1);
            y = stoi(n); // Convert the valid input to an integer
            break;           // Exit the loop if valid input is given
        } else {
            cout << "Invalid input. Please enter a single digit (0 or 1): ";
        }
    }
}

// Constructor for four_row_Random_Player
template <typename T>
four_row_Random_Player<T>::four_row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void four_row_Random_Player<T>::getmove(int& x, int& y) {
    this->dimension = 7;  // Random number between 0 and 5
    y = rand() % this->dimension;  // Random number between 0 and 6
}

template <typename T>
void execute1<T>::execute(){
    string choice;
    Player<char>* players[2];
    four_row_Board<char>* B = new four_row_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    while (true){
        cin >> choice;
        if (choice == "1"){
            players[0] = new four_row_player<char>(playerXName, 'X');
            break;
        } else if (choice == "2"){
            players[0] = new four_row_Random_Player<char>('X');
            break;
        } else{
            cout << "Invalid choice for Player 1, please try again: ";
        }
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    while (true) {
        cin >> choice;
        if (choice == "1") {
            players[1] = new four_row_player<char>(player2Name, 'O');
            break;
        } else if (choice == "2") {
            players[1] = new four_row_Random_Player<char>('O');
            break;
        } else{
            cout << "Invalid choice for Player 2, please try again: ";
        }
    }

    // Create the game manager and run the game
    GameManager<char> four_row_game(B, players);
    four_row_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }


}

#endif // four_Rows_H
