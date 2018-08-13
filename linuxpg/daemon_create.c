#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int daemon_create()
{
	int maxfd, fd;
	/* first fork to prepare setsid */
	switch(fork())
	{
	case -1: return -1;
	case 0: break;
	default: _exit(0);
	}

	if(setsid() == -1) 
		return -1;

	/* second fork to make sure no control terminal */
	switch(fork())
	{
	case -1: return -1;
	case 0: break;
	default: _exit(0);
	}

	umask(0);
	chroot("/");

	/* close all files */
	if((maxfd = sysconf(_SC_OPEN_MAX)) == -1)
		return -1;
	for(fd = 0; fd < maxfd; fd++)	
		close(fd);

	/* redirect STDIN/STOUT/STDERR */
	fd = open("/dev/null", O_RDWR);
	if(fd != STDIN_FILENO)
		return -1;
	if(dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
		return -1;
	if(dup2(fd, STDERR_FILENO) != STDERR_FILENO)
		return -1;
	return 0;
}
