#include <stdio.h>

extern int daemon_create();

int main(int argc, char *agrv[])
{
	if(daemon_create() == 0)
		sleep(60);
	else
		printf("can't create daemon\n");
	return 0;
}
