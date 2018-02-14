#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int* stuff = (int*) malloc(sizeof(int)*1);
	*stuff = 7;
	pid_t pid = fork();
	printf("Stuff is %d\n", *stuff);
	if (pid == 0)
		*stuff = 6;
}
