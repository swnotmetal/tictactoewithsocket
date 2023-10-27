#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "TicTacToe.h"

char board[3][3];
const char Player = 'X';
const char Computer = 'O';


void    resetBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void    printBoard()
{
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}
int     checkFreeSpaces()
{
    int freespaces = 9; // 3*3 an empty board has 9 freespaces

    for(int i = 0; i < 3;i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')//means the place is taken
            {
                freespaces--;
            }
        }
    }
    return  freespaces; //if it returns 0, gameover.
}
void    playerMove()
{
    int x;
    int y;

   do
   {
    printf("Enter the row #(1-3):");
    scanf("%d", &x);
    x--; //assuming the user input would not taking the arry starting from 0 into consideration.
    printf("Enter the col #(1-3):");
    scanf("%d", &y);
    y--;
    
    if(board[x][y] != ' ')
    {
        printf("Invalid Move!\n");
    }
    else
    {
        board[x][y] = Player;
        break;
    }
   } while (board[x][y] != ' ');
   
    
}
void    computerMove()
{
    // random num(char), so a seed
    srand(time(0));
    int x;
    int y;
    if(checkFreeSpaces > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = Computer;
    }
    else
    {
        printWinner(' ');
    }
}
char    checkWinner()
{
    //check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
             return board[i][0];

        }
    }
    //check cols
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
             return board[0][i];

        }
    }
    //check diagonals
    for(int i = 0; i < 3; i++)
    {
        if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
        {
             return board[0][0];
        }
    }
    for(int i = 0; i < 3; i++)
    {
        if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
             return board[0][2];
        }
    }
    return ' ';
}
void    printWinner(char winner)
{
    if(winner == Player)
    {
        printf("You Win!\n");
    }
    else if(winner == Computer)
    {
        printf("You Lose!\n");
    }
    else
    {
        printf("It is a tie!");
    }
    
}

int main()
{
    char    winner = ' ';
    char    response = ' ';

   do
   {
    resetBoard();
    while(winner == ' ' && checkFreeSpaces() != 0)
    {
        printBoard();

        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
        computerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
    }
    printBoard();
    printWinner(winner);

    printf("\nWould you like to play again? (Y/N):");
    scanf("%*c");
    scanf("%c", &response);
    response = toupper(response);
   } while (response == 'Y');
   printf("\nThanks for Playing!\n");
    
    return 0;
}