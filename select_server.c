#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#define KEY 94849
#define SEG_SIZE 200

union semun {
    int val;
    struct semid_ds *buff;
    unsigned short *array;
};
void subserver(int from_client);

int main() {
    int listen_socket;
    int client_socket;
    int f;
    int subserver_count = 0;
    char buffer[BUFFER_SIZE];
    // set of file descriptors to read from
    fd_set read_fds;
    listen_socket = server_setup();
    while (1) {
        // select() modifies read_fds
        // we must reset it at each iteration
        FD_ZERO(&read_fds); // 0 out fd set
        FD_SET(STDIN_FILENO, &read_fds); // add stdin to fd set
        FD_SET(listen_socket, &read_fds); // add socket to fd set

    // select will block until either fd is ready
    select(listen_socket + 1, &read_fds, NULL, NULL, NULL);

    // if listen_socket triggered select
    if (FD_ISSET(listen_socket, &read_fds)) {
     client_socket = server_connect(listen_socket);

     f = fork();
     subserver_count++;
     if (f == 0){
     char * memory;
       // subserver(client_socket);
           if (subserver_count - 1 == 0)
               memory = "a";
           if (subserver_count - 1 == 1)
               memory = "aa";
           if (subserver_count - 1 == 2)
               memory = "aaa";
           if (subserver_count - 1 == 3)
               memory = "aaaa";
           if (subserver_count - 1 == 4)
               memory = "aaaaa";
        send(client_socket,memory,sizeof(memory),0);
        printf("[server] subserver count: %d\n", subserver_count);
   }
     else {
       wait(NULL);
       close(client_socket);
     }
    }// end listen_socket select

    // if stdin triggered select
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      // if you don't read from stdin, it will continue to trigger select()
      fgets(buffer, sizeof(buffer), stdin);
      printf("[server] subserver count: %d\n", subserver_count);

    }// end stdin select
  }
}

void subserver(int from_client) {
    char buffer[BUFFER_SIZE];
    while (recv(from_client, buffer, sizeof(buffer),0)){
        char * memory;
        int semd = semget(KEY, 1, 0);
        struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -1;
        semop(semd, &sb, 1);
        int shmd = shmget(KEY,SEG_SIZE,0);
        memory = shmat(shmd,0,0);
        printf("memory is equal to : %s\n",memory);
        if (strlen(memory) == 0)
            memory = "a";
        else if (strlen(memory) == 1)
            memory = "aa";
        else if (strlen(memory) == 2)
            memory = "aaa";
        else if (strlen(memory) == 3)
            memory = "aaaa";
        else if (strlen(memory) == 4)
            memory = "aaaaa";
        send(from_client,memory,sizeof(memory),0);
        shmdt(memory);
        sb.sem_op = 1;
        semop(semd, &sb, 1);
        close(from_client);
        exit(0);
    }
}
