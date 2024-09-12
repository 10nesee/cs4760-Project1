#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to help user run command
void print_help() {
    printf("Usage: oss [-h] [-n process] [-s simulation] [-t iteration]\n");
}

int main(int argc, char *argv[]) {
	int option;
    	int process = 1;
    	int simulation = 1;
    	int iteration = 1;

    	while ((option = getopt(argc, argv, "hn:s:t:")) != -1) {
        	switch (option) {
            		case 'h':
                		print_help();
                		exit(0);
            		case 'n':
                		if (optarg) {
                    			process = atoi(optarg);
                		} else {
                    			fprintf(stderr, "Error: -n option\n"); 
                    			print_help(); 
					exit(EXIT_FAILURE); 
                		}
                		break;
            		case 's':
                		if (optarg) {
                    			simulation = atoi(optarg);
                		} else {
                		    	fprintf(stderr, "Error: -s option\n");
                    			print_help();
                    			exit(EXIT_FAILURE);
                		}
                		break;
            		case 't':
                			if (optarg) {
                			   	 iteration = atoi(optarg);
                			} else {
             					fprintf(stderr, "Error: -t option\n");
                    				print_help();
                    				exit(EXIT_FAILURE);
                			}
                			break;
            		default:
                		print_help();
                		exit(EXIT_FAILURE);
        	}
    	}

    	printf("process=%d\nsimulation=%d\niteration=%d\n", process, simulation, iteration);
    	
	// New child process
	pid_t pid = fork();
	
	if (pid < 0) {
		perror("fork error");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		
		// Child process
		char iteration_str[10];
		snprintf(iteration_str, sizeof(iteration_str), "%d", iteration);
		execl("./user", "user", iteration_str, (char *)NULL);

		// Excel error
		perror("execl error");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		int status;
		waitpid(pid, &status, 0);
		printf("Child process %d finished.\n", pid);
	}




	return 0;
}
	
