#include <signal.h>
#include <unistd.h>
#include <syslog.h>

extern int daemon_create();

static sig_atomic_t hupRecv = 0;
void sighupHandler(int sig)
{
	hupRecv = 1;
}


int main(int argc, char *argv[])
{
	struct sigaction sa;
	unsigned int SLEEP = 2;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sighupHandler;

	if(sigaction(SIGHUP, &sa, NULL) == -1)
		_exit(-1);

	if(daemon_create() != 0)
		_exit(-2);

	openlog(argv[0], LOG_PID|LOG_NOWAIT|LOG_CONS, LOG_LOCAL0);

	while(1)
	{
		sleep(SLEEP);
		if(hupRecv == 1)
		{
			hupRecv = 0;
			syslog(LOG_INFO, "SIGHUP Received");
		}
	}

	return 0;
}
