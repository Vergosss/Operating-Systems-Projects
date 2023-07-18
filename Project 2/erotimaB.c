#include <stdio.h>
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
typedef sem_t Semaphore;
Semaphore* cSem;
Semaphore* DataBase;


int main(){
int i;                        
pid_t pid[2];
cSem=sem_open ("cSem", O_CREAT | O_EXCL, 0644, 0);
DataBase=sem_open ("DataBase", O_CREAT | O_EXCL, 0644, 0);
shmkey = ftok ("/dev/null", 5);
shmid = shmget (shmkey, 3*sizeof(int), 0644 | IPC_CREAT);
int* rc,wc,priority;
rc=(int*)shmat(shmid, NULL, 0);
wc=rc+1;
priority=rc+2;
*wc=0;
*rc=0;
*priority=0;

for (i=0; i<2; i++)
{
pid[i]=fork ();

if (pid[i] == 0)
{
break;
}
}
//anagnostis
if(pid[0]==0){
sem_wait(cSem);
r*c=*rc+1;
sem_post(cSem);
sem_wait(DataBase);
if(*priority==0){
printf("Reading/n");
sem_wait(cSem);
*rc=*rc-1;
if(*wc!=0){
*priority=1;
}
sem_post(cSem);
}
else{
sem_wait(cSem);
if(*wc==0){
*priority=0;
}
*rc=*rc-1;
sem_post(cSem);
}
sem_post(DataBase);
}

//eggrafeas
else if(pid[0]!=0 && pid[1]==0){
sem_wait(cSem);
*wc=*wc+1;
sem_post(cSem);
sem_wait(DataBase);
if(*priority==1){
printf("Writing/n");
sem_wait(cSem);
*wc=*wc-1;
if(*rc!=0){
*priority=0;
}
sem_post(cSem);
}
else{
sem_wait(cSem);
if(*rc==0){
*priority=1;
}
*wc=*wc-1;
sem_post(cSem);
}
sem_post(DataBase);
}
else{
sem_unlink ("cSem");
sem_close(cSem);
sem_unlink ("DataBase");
sem_close(DataBase);
}








}
