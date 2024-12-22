#ifndef UNTITLED28_SUS_H
#define UNTITLED28_SUS_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// DEFINING
//---------

template<typename T>
class SUS:public Board<T>{
public:
    long long count_u=0;
    long long count_s=0;
public:
    SUS();
    ~SUS();
    bool update_board (int x , int y , T symbol) override;
    void display_board () override;
    bool is_win() override  ;
    bool can_make_SUS();
    bool is_draw()override;
    bool game_is_over()override;
    int count_wins(int i, int j);
    bool count_SUS(int x1, int y1, int x2, int y2, int x3, int y3);
   int get_countS();
   int get_countU();
   void counting(int i , int j,T symbol );

};
template <typename T>
class SUS_player : public Player<T> {
public:
    SUS_player (string name, T symbol);
    void getmove(int& k, int& r) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player(T symbol);
    void getmove(int &k, int &r) ;
};

template <typename T>
    SUS<T>::SUS() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool SUS<T>::update_board(int x, int y, T symbol) {
    if(x>=0 && x<3 && y >=0 && y<3 &&this->board[x][y]==0){
        this->board[x][y]=symbol;
        (this->n_moves)+=1;
        counting(x,y,symbol);
        return true;
    }
        return false;

}

template <typename T>
SUS<T>::~SUS(){
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
void SUS<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << endl<<"| ";
        for (int j = 0; j < this->columns; j++) {
            cout<<"("<<i<<","<<j<<")";
            cout << setw(2) << this->board[i][j] << " |";

        }
        cout << "\n_______________________________________________";
    }
    cout << endl;
    cout<< "S SCORE IS : "<<this->count_s<<" | "<< " U SCORE IS : "<<this->count_u <<"     ";

}

template<typename T>
bool SUS<T>::is_win() {
    return  false;
}
template<typename T>
bool SUS<T> ::is_draw()  {
return (this->n_moves == 9);
}
template<typename T>
bool SUS<T>::game_is_over() {

    return (this->n_moves == 9);
}


template<typename T>
int SUS<T>::get_countS(){
    return count_s;
}

template <typename T>
bool SUS<T>::can_make_SUS() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            // Check all rows, columns, and diagonals for possible "SUS" patterns
            if (this->board[i][j] == 'S') {
                // Check horizontally
                if (j + 2 < this->columns && this->board[i][j + 1] == 'U' && this->board[i][j + 2] == 0)
                    return true;
                // Check vertically
                if (i + 2 < this->rows && this->board[i + 1][j] == 'U' && this->board[i + 2][j] == 0)
                    return true;
                // Check diagonals
                if (i + 2 < this->rows && j + 2 < this->columns && this->board[i + 1][j + 1] == 'U' && this->board[i + 2][j + 2] == 0)
                    return true;
                if (i + 2 < this->rows && j - 2 >= 0 && this->board[i + 1][j - 1] == 'U' && this->board[i + 2][j - 2] == 0)
                    return true;
            }
        }
    }
    return false; // No "SUS" patterns are possible
}

template<typename T>
int SUS<T>::get_countU() {
    return count_u;
}

template<typename T>
bool SUS<T>::count_SUS(int x, int y, int i, int j, int k, int h) {
    return (this->board[x][y]=='S'&&this->board[i][j]=='U'&&this->board[k][h]=='S');
}

template<typename T>
int SUS<T>::count_wins(int i, int j) {
        int count = 0;
        count+=count_SUS(i, 0, i ,1, i, 2);
        count+=count_SUS(0, j, 1, j, 2, j);
        if (i==j) {
            count += count_SUS(0, 0, 1, 1, 2, 2);
        }
        if (i+j== 2) {
            count += count_SUS(0, 2, 1, 1, 2, 0);
        }
        return count;
    }

template<typename T>
void SUS<T>::counting(int i, int j, T symbol) {
    if(symbol=='S'){
        count_s+= count_wins(i,j);
    }
    else if(symbol=='U'){
        count_u+= count_wins(i,j);
    }
}



template<typename T>
SUS_player<T>::SUS_player(string name, T symbol):Player<T>( name,  symbol){}
template <typename T>
void SUS_player<T>::getmove(int &i, int & j) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin>>i>>j;
}


template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol):RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int &i, int &j) {
    i = rand() % 3;  // Random number between 0 and 2
    j = rand()% 3;
}


void execute3(){
    SUS <char>*board=new SUS<char>();
    string p1, p2;
    string choice;
    Player<char>* players[2];
    cout<<"Welcome to our SUS game :) ! "<<endl;
    cout<<"__________________________________"<<endl;
    cout<<"Player 1: Choose your type \n ( 1) Human    2) for Random): ";
    cin >> choice;
    while(choice!="1"&& choice!="2"){
        cout<<"invalid choice ! Enter another choice: ";
        cin>>choice;
    }if(choice=="1"){
        cout << "Enter name for Player 1 (S): ";
        cin>>p1;
        players[0]=new SUS_player(p1,'S');
    }else{
        p1="Random computer player";
        players[0]=new  SUS_Random_Player('S');
    }
    cout<<"Player 2: Choose your type \n ( 1) Human    2) for Random): ";
    cin >> choice;
    while(choice!="1"&& choice!="2"){
        cout<<"invalid choice ! Enter another choice: ";
        cin>>choice;
    }if(choice=="1"){
        cout << "Enter name for Player 2 (U): ";
        cin>>p2;
        players[1]=new SUS_player(p2,'U');
    }else{
        players[1]=new  SUS_Random_Player('U');
    }
    Player<char>* playerptr[2] = {players[0], players[1]};
    GameManager<char> game(board, playerptr);
    game.run();
    if (board->get_countU() > board->get_countS()) {
        cout << players[1]->getname() << " Wins!" << endl;
    } else if (board->get_countS() > board->get_countU()) {
        cout << players[0]->getname() << " Wins!" << endl;
    } else {
        cout << "DRAW!" << endl;
    }}










































#endif
