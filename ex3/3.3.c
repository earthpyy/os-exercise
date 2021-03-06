#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int pid, status;
	int newfd;
	char *cmd[] = { "/bin/ls", "-al", "/", 0 };

	if (argc != 2) {
		fprintf(stderr, "usage: %s output_file\n", argv[0]);
		exit(1);
	}
	if ((newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
		perror(argv[1]); /* open failed */
		exit(1);
	}

	if (!fork()) {
		printf("writing output of the command %s to \"%s\"\n", cmd[0], argv[1]);
		dup2(newfd, 1);
		execvp(cmd[0], cmd);
		perror(cmd[0]); /* execvp failed */
	} else {
		wait();
		printf("all done!");
	}
	exit(1);
}
