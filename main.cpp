#include "BoardGame_Classes.h"
#include <iostream>
#include "Pyramid.h"
using namespace std;

int main() {
    char choice;
    cout << "Choose game mode:\n";
    cout << "1. Two Players(human)\n";
    cout << "2. Play Against Computer\n";
    cin >> choice;

    PyramicBoard<char> board;

    if (choice == '1') {
        string name1, name2;
        cout << "Enter name for Player 1: ";
        cin >> name1;
        cout << "Enter name for Player 2: ";
        cin >> name2;

        HumanPlayer<char> player1(name1, 'X');
        HumanPlayer<char> player2(name2, 'O');

        Player<char>* players[2] = {&player1, &player2};
        player1.setBoard(&board);
        player2.setBoard(&board);

        GameManager<char> game(&board, players);
        game.run();

    } else if (choice == '2') {
        string name;
        cout << "Enter The player's name: ";
        cin >> name;

        HumanPlayer<char> human(name, 'X');
        Random<char> computer('O');

        Player<char>* players[2] = {&human, &computer};
        human.setBoard(&board);
        computer.setBoard(&board);

        GameManager<char> game(&board, players);
        game.run();

    } else {
        cout << "Invalid choice...\n";
    }

    return 0;
}
