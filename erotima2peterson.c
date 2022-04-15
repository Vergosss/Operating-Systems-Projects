#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <stdbool.h>
int main(){
key_t shmkey;
int shmid;//to id ths koinhs mnhmhs pou kaneis allocate
int* X;//koinh metavliti X
int* turn;//koinh metavliti pou deixnei pias diergasias einai h seira
bool* flag;//koinh metavliti flag(einai pinakas 2 theseon)

shmkey=ftok("/dev/null",5);
shmid = shmget (shmkey, 2*sizeof(int)+2*sizeof(bool), 0644 | IPC_CREAT);//kini mnimi: 4 byte gia thn turn 4 byte gia thn X kai 2 byte gia ton bool pinaka
if (shmid < 0)
{
perror ("shmget\n");
exit (1);
}
/*arxikopoihsh ths koinhs metavlitis X se 0*/
X=(int*)shmat(shmid,NULL,0);
turn=X+1;//o turn deixnei sto deytero int ths koinhs mnhmhs
flag=X+2;
*X=0;
*turn=0;
*flag=false;
*(flag+1)=false;

int tmp,temp;

pid_t pid[2];
int i;
for(i=0;i<2;i++){
pid[i]=fork();
if(pid[i]==0){
    break;
}
}
if(pid[0]!=0 && pid[1]!=0){
for(i=0;i<2;i++){
wait(&temp);
}
}
/*-----dimiourgoume ta dio paidia------*/
//1o paidi
else if(pid[0]==0){
*flag=true;//deixnoume oti to proto paidi thelei na bei sto critical section
*turn=1;//dilonoume oti h allh diergasia meta tha einai h seira ths na ektelesei critical section
while(turn==1 && *(flag+1)==true);
for(i=1;i<=500;i++){
tmp=(*X);
tmp=tmp+1;
(*X)=tmp;
}
*flag=false;
}
else if(pid[0]!=0 && pid[1]==0){
*(flag+1)=true;//deixnoume oti to deytero paidi thelei na bei sto critical section
*turn=0;
while(turn==0 && *(flag)==true);
for(i=1;i<=500;i++){
tmp=(*X);
tmp=tmp+1;
(*X)=tmp;
}
*(flag+1)=false;
}


}
