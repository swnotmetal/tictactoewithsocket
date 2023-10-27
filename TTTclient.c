#include "TicTacToe.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

int TCPclient()
{
    // create a socket.
    int local_network_socket;
    local_network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // address for the socket.
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons (9666); /* Registered Ports (1024-49151):Available for applications, but they are not standardized in the same way as well-known ports. 
    They are assigned by the Internet Assigned Numbers Authority (IANA) to the requesting organization.*/
    server_addr.sin_addr.s_addr = INADDR_ANY; // or 0.0.0.0 if local

    int connection_status = connect(local_network_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
    
    // check if everything is ok with the connection
    if (connection_status == -1)
    {    
        printf("Error in connection\n\n");
        return 1;
    }

    char    response;
    char    winner;

    do
    {
        //checking the current state of the board
        recv(local_network_socket, board, sizeof(board), 0);
        printBoard();
        
        //checking playermove
        playerMove();
        send(local_network_socket,board, sizeof(board), 0);

        //receive the final stage of the board
        recv(local_network_socket, board, sizeof(board), 0);
        recv(local_network_socket, &winner,sizeof(winner), 0 );

        printBoard();
        printWinner(winner);

        printf("\nWould you like to play again? (Y/N):");
        scanf("%*c");
        scanf("%c", &response);
        response = toupper(response);

    } while (response == 'Y'); //repeats the do-loop again

    printf("Thanks for playing!");
    close(local_network_socket);

    return 0;
}