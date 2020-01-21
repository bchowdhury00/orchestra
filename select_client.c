#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


char * getLink(int n){
  FILE * f = fopen("links.txt", "r");
  int linknum = 0;
  char *input = malloc(200 * sizeof(char));
  while(fgets(input, 200 * sizeof(char), f)){
    if (n == linknum){
	  fclose(f);
      return input;
    } else {
      linknum++;
    }
  }
}

int main(int argc, char **argv) {
    int server_socket;
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    if (argc == 2)
        server_socket = client_setup( argv[1]);
    else
        server_socket = client_setup( TEST_IP );
    int newbuffer;
    while (1) {
        //printf("enter data: ");
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
        FD_SET(server_socket, &read_fds); //add socket to fd set
        //select will block until either fd is ready
        select(server_socket + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buffer, sizeof(buffer), stdin);
            *strchr(buffer, '\n') = 0;
            write(server_socket, buffer, sizeof(buffer));
            read(server_socket, buffer, sizeof(buffer));
            printf("received: [%s]\n", buffer);
        }//end stdin select

        //currently the server is not set up to
        //send messages to all the clients, but
        //this would allow for broadcast messages
        if (FD_ISSET(server_socket, &read_fds)) {
            char * message = "send me a";
            write(server_socket,message,sizeof(message));
            recv(server_socket, buffer, sizeof(buffer),0);
	           if (strlen(buffer) == 1) {
                   newbuffer = 0;
                   break;
               }
               if (strlen(buffer) == 2) {
                   newbuffer = 1;
                   break;
               }
               if (strlen(buffer) == 3) {
                   newbuffer = 2;
                   break;
               }
               if (strlen(buffer) == 4) {
                   newbuffer = 3;
                   break;
               }
               if (strlen(buffer) == 5) {
                   newbuffer = 4;
                   break;
	             }
             }
         } //end while loop
      // printf("[SERVER BROADCAST] [%c]\n", buffer);
      // printf("enter data: ");
      //the above printf does not have \n
      //flush the buffer to immediately print
      //fflush(stdout);
  //end socket select
  char *url;
  url = getLink(newbuffer);
  char call[256];
  strcpy(call, "xdg-open ");
  strcat(call, url); // append url
  system(call); // opens music in browser
}
