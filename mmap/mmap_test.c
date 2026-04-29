/************************************************
 * Title:		mmap_test	        			*
 * Creator:		John J. Coleman					*
 * Creation Date:	2026.04.29					*
 * Modified Date:	2026.04.29					*
 * 												*
 * Description:									*
 * mapping anonymous memory from a user space 	*
 * program which then pauses for kernely layer 	*
 * analysis.									*
 ************************************************/

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

void signal_handler()
{
	fprintf(stdout, "Signal received, surpassing pause.\n");
}

int main(int argc, char *argv[])
{
	char *address;

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);

	address = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(address == MAP_FAILED)
	{
		fprintf(stderr, "mmap failed.\n");
		return -1;
	}
	fprintf(stdout, "mmap address: %p\n", address);
	pause();

	*address = 10;
	fprintf(stdout, "mmap address: %p\n", address);
	pause();

	return 0;
}
