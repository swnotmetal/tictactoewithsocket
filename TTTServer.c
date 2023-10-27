#include "TicTacToe.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void    updateBoard(int move, char player)
    {
        int x = (move - 1) / 3;
        int y = (move - 1) % 3;

        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ')
        {
            board[x][y] = player;
        }
        else
        {
            printf("Invalid Move!\n");
        }
    }

int TCPservice()
{
    char server_message[512] = "TTTServer reached.";

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9666);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket,(struct sockaddr *) &server_addr, sizeof(server_addr));

    do
    {
        resetBoard();

        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);
        char winner;

        char    response;
        do
        {
            printBoard();
            send(client_socket, board, sizeof(board), 0);
            recv(client_socket, &response, sizeof(response), 0);
            updateBoard(response, Player);

            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            computerMove();
            winner = checkWinner();

        } while (winner == ' ' && checkFreeSpaces() != 0);

        send(client_socket, board, sizeof(board), 0);
        send(client_socket, &winner, sizeof(winner), 0);

        close(client_socket);
        

    } while (1);

    close(server_socket);
    
}