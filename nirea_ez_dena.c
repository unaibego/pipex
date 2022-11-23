#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	int	fd1[2];
	int	pid;

	pipe(fd1);
	pid = fork();

	if (pid == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO); 
		close(fd1[1]);
		execlp("/sbin/ping", "ping", "-c", "3", "google.com" , NULL);
	}
	else
	{
		close(fd1[1]);
		dup2(fd1[0], STDIN_FILENO);
		close(fd1[0]);
		execlp("/usr/bin/wc","wc", "-l",NULL);
	}
	wait(NULL);
	wait(NULL);

	return 0;
  	
}