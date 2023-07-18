#include <unistd.h>
#include <stdio.h>
int main()
{
int i, pid;
pid = fork();

if (pid > 0)
{
sleep(2);
return(0);
}
for (i=0; i<3; i++)
{
printf("My parent is %d\n", getppid());
sleep(1);
}

return (0);
}
