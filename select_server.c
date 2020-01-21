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
#define KEY 93847
#define SEG_SIZE sizeof(int)

void process(char *s);
void subserver(int from_client);

int main() {
    int listen_socket;
    int client_socket;
    int f;
    int subserver_count = 0;
    char buffer[BUFFER_SIZE];
    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1){
        printf("error %d: %s\n", errno, strerror(errno));
        exit(0);
    }
    else {
        union semun us;
        us.val = 1;
        semctl(semd, 0, SETVAL, us);
        printf("semaphore created\n");
    }
    if ((shmd = shmget(KEY,SEG_SIZE, IPC_CREAT | IPC_EXCL | 0644)))
    printf("shared memory segment created\n");
    else{
        printf("error %d: %s\n", errno, strerror(errno));
        exit(0);
    }
    //set of file descriptors to read from
    fd_set read_fds;
    listen_socket = server_setup();
    while (1) {
        //select() modifies read_fds
        //we must reset it at each iteration
        FD_ZERO(&read_fds); //0 out fd set
        FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
        FD_SET(listen_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(listen_socket + 1, &read_fds, NULL, NULL, NULL);

    //if listen_socket triggered select
    if (FD_ISSET(listen_socket, &read_fds)) {
     client_socket = server_connect(listen_socket);

     f = fork();
     if (f == 0)
       subserver(client_socket);
     else {
       subserver_count++;
       close(client_socket);
     }
    }//end listen_socket select

    //if stdin triggered select
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      //if you don't read from stdin, it will continue to trigger select()
      fgets(buffer, sizeof(buffer), stdin);
      printf("[server] subserver count: %d\n", subserver_count);
    }//end stdin select
  }
}

void subserver(int client_socket) {
    int * memory;
    int semd = semget(KEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    semop(semd, &sb, 1);
    int shmd = shmget(KEY,SEG_SIZE,0);
    memory = shmat(shmd,0,0);
    char c = 48 + memory;
    write(client_socket,c,sizeof(c));
    memory = memory + 1;
    shmdt(memory);
    sb.sem_op = 1;
    semop(semd, &sb, 1);
    close(client_socket);
    exit(0);
}
