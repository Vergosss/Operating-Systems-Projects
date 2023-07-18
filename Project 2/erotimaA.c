#include <stdio.h>
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#define N 2
typedef sem_t Semaphore;
Semaphore* s; //epeidh to heap einai koino se oles tis diergasies prepei na epitrepoume mono se mia ana pasa stigmh na peirazei thn p kai to heap
int main(){
key_t shmkey;
int shmid;
shmkey = ftok ("/dev/null", 5);
shmid = shmget (shmkey, (N+2)*sizeof(int), 0644 | IPC_CREAT);//koinh mnhmh pou apoteleitai apo ton pointer sto heap array metavliti size diladi prosorino megethos tou pinaka kai p to athrisma pou theloume
int* p;
int* heap;
int* size;
p=(int*)shmat(shmid, NULL, 0);
*p=0; //vazoume thn metavliti p sth koinh mnhmh kai thn arxikopoioume se 0
heap=p+1;
size=p+2;
*size=0;
*(heap+0)=-1;
//arxikopoihsh tou heap
eisagogi();
int   i;
pid_t pid[2];

s = sem_open ("Semaphore", O_CREAT | O_EXCL, 0644, 1);//arxikopoihsh shmaforou se 1,epeita kapoia apo tis N diergasies tha ton riksei sto 0 kai tha bei sth krisimh perioxh
for (i=0; i<2; i++)
{//dhmiourgoume dio paidia meso ths fork
pid[i] = fork ();
if (pid[i] == 0)
{
break;
}
}
if(pid[0]==0){
sem_wait(s);//sygxronizoume katalila th diergasia oste na borei na peiraksei to p mono ayth eno oi ales diegasies de tha dikaountai prosvasi
int i;
for(i=1;i<=10;i++){
(*p)=(*p)+getMin();//an eixame N diergasies genika tote to orio sto for tha htan pali 10 logv tou oti 10*N/N=10
}
sem_post(s);
}
else if(pid[0]!=0&&pid[1]==0){
int j;
sem_wait(s);
for(j=1;j<=10;j++){
(*p)=(*p)+getMin();
}
sem_post(s);
}

}
int getMin(){
int min,last,temp,paidi;
min=*(heap+1);
last=*(heap+(*size)--)
for(temp=1;temp*2<=*(size);temp=child){
child=child*2;
if (child != *(size) && *(heap+child + 1)) < *(heap+child) {
child++;
}//synarthsh pou pernei to elaxisto apo to heap array kai epeita to diagrafei
if(last>*(heap+child)){
*(heap+temp)=*(heap+child);
}
else{
break;
}
*(heap+temp)=last;
return min;
}


}
void eisagogi(){
int i;
for(i=1;i<=10*N;i++){
*(size)= *(size)+1;
*(heap+size)=i;
int temp=*size;
while (*(heap+temp/2) >i) {
*(heap+temp) = *(heap+ temp/ 2);
temp /= 2;
}
*(heap+temp)=i;
}//synarthsh pou eisage tis times tis ekfonisis sto array
}
