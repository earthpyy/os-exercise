#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid = fork();
	int exit;
	if (pid != 0) {
		//wait(&exit);
		waitpid(pid);
	}
	printf("Hello World\n: %d\n", pid);
}
