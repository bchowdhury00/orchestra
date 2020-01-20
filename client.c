#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char ** links;
void compile_links(){
  FILE * f = fopen("links.txt", "r");
  int linknum = 0;
  char *input = malloc(200 * sizeof(char));
  while(fgets(input, 200 * sizeof(char), f)){
    links[linknum] = input;
    linknum++;
  }
}

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
    //if buffer
  }
}
