#include <stdio.h>
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
typedef sem_t Semaphore;
Semaphore* s1;
Semaphore* s2;
Semaphore* s3;
Semaphore* s4;



int main(){
int   i;
pid_t pid[5];
s1 = sem_open("Sem1", O_CREAT | O_EXCL, 0644, 0);
s2 = sem_open("Sem2", O_CREAT | O_EXCL, 0644, 0);
s3 = sem_open("Sem3", O_CREAT | O_EXCL, 0644, 0);
s4 = sem_open("Sem4", O_CREAT | O_EXCL, 0644, 0);


for (i=0; i<5; i++)
{
pid[i] = fork();

if (pid[i] == 0)
{
break;
}
}
if (pid[0] == 0){
system("echo system call 1");
sem_post(s1); //signal ton shmaforo
}

else if (pid[0] != 0 && pid[1] == 0)
{
system("echo system call 2");
sem_post (s2);
}

else if (pid[0] != 0 && pid[1] != 0 && pid[2] == 0)
{
system("echo system call 3");
sem_post (s4);
}

else if (pid[0] != 0 && pid[1] != 0 && pid[2] != 0 && pid[3] == 0)
{
sem_wait(s1);
sem_wait(s2);           /* UP operation */
system("echo System call 4");
sem_post (s3);           /* DOWN operation */
}

else if (pid[0] != 0 && pid[1] != 0 && pid[2] != 0 && pid[3] != 0 && pid[4]==0)
{
sem_wait(s3);
sem_wait(s4);           /* UP operation */
system("echo system call 5");
}
else{
sem_unlink ("Sem1");
sem_close(s1);
sem_unlink ("Sem2");
sem_close(s2);
sem_unlink ("Sem3");
sem_close(s3);
sem_unlink ("Sem4");
sem_close(s4);
}
}
