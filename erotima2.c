#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
int main(){
key_t shmkey;
int shmid;
int* X;

shmkey=ftok("/dev/null",5);
shmid = shmget (shmkey, sizeof(int), 0644 | IPC_CREAT);//orizeis to id ths koinhs mnhmhs
if (shmid < 0)
{
perror ("shmget\n"); // elegxos an egine lathos kata th dhmiourgia ths koinhs mnimis.
exit (1);
}
/*arxikopoihsh ths koinhs metavlitis X se 0*/
X=(int*)shmat(shmid,NULL,0);
*X=0;
int tmp,temp;//h tmp einai topikh gia kathe diergasia opote de th vazoume sth koinh mnhmh

pid_t pid[2];
int i;
for(i=0;i<2;i++){
pid[i]=fork(); // dhmiourgia 2 paidion
if(pid[i]==0){
    break;
}
}
if(pid[0]!=0 && pid[1]!=0){
for(i=0;i<2;i++){
wait(&temp); //o pateras tha perimenei thn oloklirosi ton 2 paidion tou kai meta termatizei.
}
}
/*-----dimiourgoume ta dio paidia------*/
//1o paidi
else if(pid[0]==0){
for(i=1;i<=500;i++){
tmp=(*X);
tmp=tmp+1;
(*X)=tmp;
}
}
//2o paidi
else if(pid[0]!=0 && pid[1]==0){
for(i=1;i<=500;i++){
tmp=(*X);
tmp=tmp+1;
(*X)=tmp;
}
}


}
