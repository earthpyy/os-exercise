#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int sig)
{
	char c;
	printf("Ouch, you just hit Ctrl-C?. Do you really want to quit [y/n]?");
	c = getchar();
	if (c == 'Y' || c == 'y')
		exit(0);
}

int main()
{
	signal(SIGINT, sigint_handler);
	while(1);
}
