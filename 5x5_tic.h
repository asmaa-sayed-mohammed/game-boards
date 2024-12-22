
#ifndef UNTITLED28_5X5_TIC_H
#define UNTITLED28_5X5_TIC_H

#include "BoardGame_Classes.h"
#include <iomanip>
template <typename T>
class X5x5O:public Board<T> {
public:
    X5x5O ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    long long count3(T symbol);

};

// human player
template <typename T>
class X5x5O_HP:public Player<T>{
public:
    X5x5O_HP(string name,T symbol);
    void getmove(int &x , int& y);
};

// Random player
template <typename T>
class X5x5O_RP:public RandomPlayer<T>{
public:
    X5x5O_RP(T symbol);
    void getmove(int &x , int& y) ;
};



//// implementation
// ______________
template <typename T>
X5x5O<T>::X5x5O() {
    this->rows = 5;
    this->columns = 5;
    this->board = new T*[5];
    for (int i = 0; i < 5; i++) {
        this->board[i] = new T[5];
        for (int j = 0; j < 5; j++) {
            this->board[i][j] = 0;
        }
    }
}

// display function
template <typename T>
void X5x5O<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << endl<<"| ";
        for (int j = 0; j < this->columns; j++) {
           cout<<"("<<i<<","<<j<<")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n_______________________________________________";
    }
    cout << endl;
}

// counting function
template <typename T>
long long X5x5O<T>::count3(T symbol){
    long long count=0;

    //horizontal checking
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(j+2< this->columns){
                if(this->board[i][j]==this->board[i][j+1]&&this->board[i][j+1]==this->board[i][j+2]&&this->board[i][j+1]==symbol){
                    count+=1;
                }
            }
        }
    }

    //vertical checking
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 3; ++i) {
            if(i+2<this->rows){
                if(this->board[i][j]==this->board[i+1][j]&&this->board[i+1][j]==this->board[i+2][j]&&this->board[i+1][j]==symbol){
                    count+=1;
                }
            }
        }
    }

    for (int i = 0; i <3; i++) {
        for (int j = 0; j <3; j++) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                count+=1;
            }
        }
    }
    for (int i = 2; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol && this->board[i - 1][j + 1] == symbol && this->board[i - 2][j + 2] == symbol) {
                count+=1;
            }
        }
    }
    return count;

}

// update function
template <typename T>
bool X5x5O<T>::update_board(int x, int y, T symbol) {
    if(x>=0 && x<5 && y >=0 && y<5 &&this->board[x][y]==0){
        this->board[x][y]=symbol;
        (this->n_moves)+=1;
        return true;
    }else{
        return false;
    }
}

// draw function
template <typename T>
bool X5x5O<T>::is_draw() {
    return (false);
}

//game over
template <typename T>
bool X5x5O<T>::game_is_over() {
    return (this->n_moves==24);
}

template <typename T>
bool X5x5O<T>::is_win() {
    return 0;
}

//inializing the players
template <typename T>
X5x5O_HP<T>::X5x5O_HP(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X5x5O_HP<T>::getmove(int &x, int & y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


template <typename T>
X5x5O_RP<T>::X5x5O_RP(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    this->dimension=5;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X5x5O_RP<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() %this->dimension;
}

using namespace std;

template <typename T>
class Gamemanager2 {
private:
    Player<T>* players[2];
    X5x5O<T>* board;
    int i;

public:

    //constructor
    Gamemanager2() {
        board =new X5x5O<T>();
        i = 0;
    }

    //a destructor to save memory
    ~Gamemanager2() {
        delete board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }

    void execute2() {
        string playerxn, playeron;
        string choice;
        cout<<"Welcome to our 5x5 Tic Tac Toe :) ! "<<endl;
        cout<<"__________________________________"<<endl;
        cout<<"Player 1: Choose your type \n ( 1) Human    2) for Random): ";
        cin >> choice;
        while(choice!="1"&& choice!="2"){
            cout<<"invalid choice ! Enter another choice: ";
            cin>>choice;
        }if(choice=="1"){
            cout << "Enter name for Player 1 (X): ";
            cin >> playerxn;
            players[0]=new X5x5O_HP<T> (playerxn,'X');
        }else{
            players[0]=new X5x5O_RP<T>('X');
        }

        cout << "Player 2: Choose your type \n (1) Human  2)for Random): ";
        cin >> choice;
        if(choice=="1"){
            cout << "Enter name for Player 2 (O): ";
            cin >> playeron;
            players[1] = new X5x5O_HP<T>(playeron,'O');
        }else{
            players[1] = new X5x5O_RP<T>('O');
        }
        Player<T>* playerptr[2] = {players[0], players[1]};
        GameManager<T> gameManager(board, playerptr);
        gameManager.run();
        int x=board->count3('X');
        int o=board->count3('O');
        if(!playerxn.size()){
            playerxn="Random Computer Player";
        }
        if(!playeron.size()){
            playeron="Random Computer Player";
        }
        if(x>o){
            cout<<playerxn<<" (X) wins with 3 sequence wins: "<< x<<" sequences !!!!" <<endl;
        }else if(o>x){
            cout<<playeron<<" (O) wins with 3 sequence wins: "<< o<<" sequences !!!!" <<endl;
        }
        else{
            cout<<"DRAW! each of 3 sequence: "<<x<<endl;
        }

    }
};

#endif




