#include <signal.h>

void sighupHandler(int sig)
{
}


int main(int argc, char *argv[])
{
	struct sigation sa;
	sa.sa_flag 
	sa.sa_handler = sighupHandler;

	return 0;
}
