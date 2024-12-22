#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame.h"
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()
#include <array>

using namespace std;

constexpr int BOARD_SIZE = 3;

template <typename T>
class numerical_board : public Board<T> {
public:
    array<array<int, BOARD_SIZE>, BOARD_SIZE> board;  // Fixed-size 2D array for board
    numerical_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class numerical_Player : public Player<T> {
public:
    numerical_board<T>* board;
    T current_number;
    bool usedNumbers[10];  // Array to track used numbers (1 to 9)

    numerical_Player(string name, T symbol, numerical_board<T>* board);
    void getmove(int& x, int& y);
};

template <typename T>
class numerical_Random_Player : public RandomPlayer<T> {
private:
    T current_number;
    numerical_board<T>* board;
    bool usedNumbers[10];  // Array to track used numbers (1 to 9)

public:
    numerical_Random_Player(T symbol, numerical_board<T>* board);
    void getmove(int& x, int& y);
};

class execute_numerical{
public:
    execute_numerical();
};

//--------------------------------------- IMPLEMENTATION

// Constructor for numerical_board
template <typename T>
numerical_board<T>::numerical_board() : Board<T>() {  // Explicitly call the base class constructor
    this->n_moves = 0;  // Initialize moves count
    // Initialize the board to 0 (empty)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->board[i][j] = 0;
        }
    }
}

template <typename T>
bool numerical_board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || this->board[x][y] != 0) {
        return false;
    }
    this->board[x][y] = mark;
    this->n_moves++;
    return true;
}

template <typename T>
void numerical_board<T>::display_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "\n| ";
        for (int j = 0; j < BOARD_SIZE; j++) {
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
bool numerical_board<T>::is_win() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) {
            return true;
        }
        if (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[0][i] != 0 &&  this->board[1][i] !=0 && this->board[2][i] != 0) {
            return true;
        }
    }
    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) {
        return true;
    }
    if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 && this->board[0][2] != 0 &&  this->board[1][1] != 0 && this->board[2][0] != 0) {
        return true;
    }
    return false;
}

template <typename T>
bool numerical_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool numerical_board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for numerical_Player
template <typename T>
numerical_Player<T>::numerical_Player(string name, T symbol, numerical_board<T>* board) : Player<T>(name, symbol), board(board) {
    fill(begin(usedNumbers), end(usedNumbers), false);  // Initialize used numbers
}

template <typename T>
void numerical_Player<T>::getmove(int& x, int& y) {
    T number;
    cout << "\nPlayer " << this->symbol << ", enter your move (x y): ";
    while (true) {
        cin >> x >> y;
        if (board->board[x][y] != 0) {
            cout << "This cell has been already used, please try another cell: ";
        } else {
            break;
        }
    }

    cout << "Insert the number (1-9): ";
    while (true) {
        cin >> number;
        if (number < 1 || number > 9) {
            cout << "Invalid number, please try again: ";
        } else if (usedNumbers[number]) {
            cout << "This number has been already used, please try another: ";
        } else if ((this->symbol == 1 && number % 2 == 0) || (this->symbol == 2 && number % 2 != 0)) {
            cout << "Invalid number, player " << this->symbol << " should insert "
                 << (this->symbol == 1 ? "odd" : "even") << " numbers only: ";
        } else {
            usedNumbers[number] = true;
            board->update_board(x, y, number);
            break;
        }
    }
    board->display_board();
}

// Constructor for numerical_Random_Player
template <typename T>
numerical_Random_Player<T>::numerical_Random_Player(T symbol, numerical_board<T>* board) : RandomPlayer<T>(symbol), board(board) {
    fill(begin(usedNumbers), end(usedNumbers), false);  // Initialize used numbers
}

template <typename T>
void numerical_Random_Player<T>::getmove(int& x, int& y) {
    // Find a random empty cell
    while (true) {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
        if (board->board[x][y] == 0) {
            break;
        }
    }

    // Generate random number for this move
    T randomNumber = (this->symbol == 1) ? 1 + 2 * (rand() % 5) : 2 + 2 * (rand() % 4);

    // Check if random number is already used
    if (!usedNumbers[randomNumber]) {
        usedNumbers[randomNumber] = true;
        board->update_board(x, y, randomNumber);
    } else {
        getmove(x, y);  // Retry if random number has been used already
    }
    board->display_board();
}

execute_numerical::execute_numerical() {
    string name1, name2;
    int playerChoice1, playerChoice2;

    // Ask Player 1 for their name and whether they want to be human or random
    cout << "Enter Player 1's name: ";
    cin >> name1;
    cout << "Choose Player 1's type (1 for Human, 2 for Random): ";
    cin >> playerChoice1;

    // Ask Player 2 for their name and whether they want to be human or random
    cout << "Enter Player 2's name: ";
    cin >> name2;
    cout << "Choose Player 2's type (1 for Human, 2 for Random): ";
    cin >> playerChoice2;

    // Create a numerical board
    numerical_board<int> board;

    // Create Player 1
    Player<int>* player1;
    if (playerChoice1 == 1) {
        player1 = new numerical_Player<int>(name1, 1, &board); // Player 1 as Human
    } else {
        player1 = new numerical_Random_Player<int>(1, &board); // Player 1 as Random
    }

    // Create Player 2
    Player<int>* player2;
    if (playerChoice2 == 1) {
        player2 = new numerical_Player<int>(name2, 2, &board); // Player 2 as Human
    } else {
        player2 = new numerical_Random_Player<int>(2, &board); // Player 2 as Random
    }

    // Set the board for the players
    player1->setBoard(&board);
    player2->setBoard(&board);

    // Create a game manager and pass the board and players
    Player<int>* players[] = {player1, player2};
    GameManager<int> gameManager(&board, players);

    int x, y; // Variables to hold the player's move

    // Run the game loop with alternating players
    while (!board.game_is_over()) {
        // Player 1's turn
        cout << player1->getname() << "'s turn: \n";
        player1->getmove(x, y); // Pass x and y as arguments for the player's move
        board.display_board(); // Display the board after Player 1's move
        if (board.game_is_over()) {
            if (board.is_win()) {
                cout << player1->getname() << " wins!\n";
                break;
            }
        }

        // Player 2's turn (Computer Player)
        cout << player2->getname() << "'s turn: \n";
        player2->getmove(x, y); // Pass x and y as arguments for the player's move
        board.display_board(); // Display the board after Player 2's move
        if (board.game_is_over()) break; // Check if Player 2 wins or it's a draw
        if (board.is_win()) {
            cout << player2->getname() << " wins!\n";
            break;
        }
    }

    // If it's a draw
    if (board.is_draw()) {
        cout << "It's a draw!\n";
    }

    // Clean up dynamically allocated memory
    delete player1;
    delete player2;

}

#endif // NUMERICAL_TIC_TAC_TOE_H
