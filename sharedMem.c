#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#define KEY 94847
#define SEG_SIZE 200

union semun {
    int val;
    struct semid_ds *buff;
    unsigned short *array;
};

int main() {
    int shmd;
    if (shmd = shmget(KEY,SEG_SIZE, IPC_CREAT | IPC_EXCL | 0644))
        printf("shared memory segment created\n");
    else{
        printf("error %d: %s\n", errno, strerror(errno));
        exit(0);
    }
    int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
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
}
