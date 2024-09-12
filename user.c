#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int interations = atoi(argv[1]);
		
	// Current process id
	pid_t pid = getpid();
	
	// Parent id
	pid_t ppid = getppid();
	
	// Loop iterations
	for (int i = 1; i <= interations; i++) {
		printf("USER PID:%d PPID:%d Iterations:%d before sleeping\n", pid, ppid, i);
		sleep(1);
		printf("USER PID:%d PPID:%d Iterations:%d after sleeping\n", pid, ppid, i);
	}

	return 0;
	
}
