//
//  main.cpp
//  tic-tac-toe
//
//  Created by Mili N. on 10/15/22.
//

#include <iostream>
#include <string.h>
using namespace std;

// Initializing board to 0s
void initBoard(int *board[3], int boardDim) {
    for (int i = 0; i < boardDim; i++) {
        board[i] = new int[boardDim];
    }
}

// Pretty print board w count
void printBoard(int *board[3], int boardDim) {
    // Print out a newline
    cout  << "\n";
    int count = 0;
    for (int i = 0; i < boardDim; i++) {
    
        for (int j = 0; j < boardDim; j++) {
            // Keeping count
            count ++;
            // Spot string
            string spot;
            // Setting display string for spot
            if (board[i][j] == 0) {
                spot = "__";
            } else if (board[i][j] == 1) {
                spot = "❌";
            } else if (board[i][j] == -1) {
                spot = "⭕️";
            }

            // New line after every row
            if (count % 3 == 0) {
                cout  << count << " [" << spot << "]" << endl;
            } else {
                cout << count << " [" << spot << "] ";
            }

        }
    }
}

// Player choice
int getPlayerChoice(int boardDim, string currentPlayerName) {
    // initialize to non-valid choice
    int choice = -1;
    while (choice < 0 || choice > boardDim*boardDim) {
        cout << "\n" << currentPlayerName << " please pick a spot (1-9): ";
        cin >> choice;
    }
    return choice;
}
// Makes player choice and returns the choice
void addPlayerChoice(int *board[3], int boardDim, string currentPlayerName, int currentPlayerFlag) {
    // initialize to non-valid choice
    int choiceIndex = -1;

    // Has player finished picking a valid spot
    bool finishedPick = false;

    while (!finishedPick) {
        // Getting a valid player choice eg. for 3x3 board valid choices are 1 - 9
        int choice = getPlayerChoice(boardDim, currentPlayerName);
    
        int count = 0;
        for (int i = 0; i < boardDim; i++) {
        
            for (int j = 0; j < boardDim; j++) {
                // Keeping count
                count ++;

                // found chosen index
                if (count == choice) {
                    // Empty spot
                    if (board[i][j] == 0) {
                        board[i][j] = currentPlayerFlag;
                        finishedPick = true;

                    } else if (board[i][j] == currentPlayerFlag) {
                        cout << "spot taken by you" << endl;
                    } else if (board[i][j] == currentPlayerFlag * -1) {
                        cout << "spot taken by other" << endl;
                    }
                }

            }
        }
    }

}

// Evaluate board for isWinning combos
bool evalBoard(int *board[3], int boardDim, int currentPlayerFlag) {
    int count = 0;
    bool isWin = false;

    for (int i = 0; i < boardDim; i++) {
    
        for (int j = 0; j < boardDim; j++) {
            // Keeping count
            count++;

            // Check 1st col right
            if (j == 0) {
                // Checking current, 1 to right, and 2 to right spot
                if (board[i][j] == currentPlayerFlag && board[i][j+1] == currentPlayerFlag && board[i][j+2] == currentPlayerFlag) {
                    isWin = true;
                    break;
                }
            }

            // check 1st row down
            if (i == 0) {
                 // Checking current, same col 1 row down, same col 2 rows down
                if (board[i][j] == currentPlayerFlag && board[i+1][j] == currentPlayerFlag && board[i+2][j] == currentPlayerFlag) {
                    isWin = true;
                    break;
                }
            }

            // check left diag
            // Check for the top left spot
            if (i == 0 && j == 0) {
                if (board[i][j] == currentPlayerFlag && board[i+1][j+1] == currentPlayerFlag && board[i+2][j+2] == currentPlayerFlag) {
                    isWin = true;
                    break;
                }
            }

            // check right diag
            // Check for the top right spot
            if (i == 0 && j == 2) {
                if (board[i][j] == currentPlayerFlag && board[i-1][j-1] == currentPlayerFlag && board[i+2][j-2] == currentPlayerFlag) {
                    isWin = true;
                    break;
                }
            }

        }
    }
    return isWin;
}

int main()
{
    // Must be 3
    int boardDim = 3;

    //Board status
    //0 = unitinialized
    //1 = X p1
    //-1 = O p2
    int *board[boardDim];

    initBoard(board, boardDim);

    printBoard(board, boardDim);

    bool hasWinner = false;
    bool p1Turn = true;
    string currentPlayerName = "Player 1";
    int totalTurns = boardDim*boardDim;
    int turnsCount = 0;
    bool isTie = false;

    // Main game loop for each turn
    while (!hasWinner) {
        // Check amount of turns
        if (turnsCount == totalTurns) {
            isTie = true;
            break;
        }
        int choice;
        // Get current player name
        currentPlayerName = p1Turn ? "Player 1" : "Player 2";
        // Player num for board 1 for p1, -1 for p2
        int currentPlayerFlag = p1Turn ? 1 : -1;
        if (p1Turn) {
            // player one picks slot
            addPlayerChoice(board, boardDim, currentPlayerName, currentPlayerFlag);
            printBoard(board, boardDim);

            // board is evaluated
            hasWinner = evalBoard(board, boardDim, currentPlayerFlag);

            // set p1turn to false
            p1Turn = false;
        } else {

            // player two picks slot
            addPlayerChoice(board, boardDim, currentPlayerName, currentPlayerFlag);
            printBoard(board, boardDim);

            // board is evaluated
            hasWinner = evalBoard(board, boardDim, currentPlayerFlag);

            // set p1turn to true
            p1Turn = true;
        }
        turnsCount++;
    }
    if (isTie) {
        cout << "\n" <<"Its a tie!" << endl;
    } else {
        cout << "\n" << currentPlayerName <<" is the superior tic-tac-toer!" << endl;
    }

}

// TODO
// [] find a way to cross compile to windows .exe
//    - already have mingw-w64
// [] add option to vs computer
