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
#define SEG_SIZE 200

union semun {
    int val;
    struct semid_ds *buff;
    unsigned short *array;
};
void subserver(int from_client);

int main() {
    int semd;
    int shmd;
    semd = semget(KEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    shmd = shmget(KEY,SEG_SIZE,0);
    semd = semget(KEY,1,0);
    semop(semd, &sb, 1);
    shmctl(shmd,IPC_RMID,0);
    printf("removed shared memory")
    semctl(semd,IPC_RMID, 0);
    printf("removed semaphore")
}