#ifndef TICTACTOE_H
#define TCTTACTOE_H

extern  char board[3][3];
extern  const char Player;
extern  const char Computer;

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char winner);
void updateBoard(int move, char player);

#endif  