#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i;
	int pid;
     pid = fork();
	for (i=1; i<=500; i++)
	    if (pid > 0)
		   printf("%3i (parent)\n", i);
		else
		   printf("%3i (child)\n", i);
		return (0);
}
