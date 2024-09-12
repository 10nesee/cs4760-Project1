#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

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
                process = atoi(optarg);
                break;
            case 's':
                simulation = atoi(optarg);
                break;
            case 't':
                iteration = atoi(optarg);
                break;
            default:
                print_help();
                exit(EXIT_FAILURE);
        }
    }

    printf("process=%d\nsimulation=%d\niteration=%d\n", process, simulation, iteration);

    int processes = 0;
    int active_process = 0;
    pid_t pid;

    // Parent process forks child processes
    while (processes < process) {
        if (active_process < simulation) {
            // New child process
            pid = fork();

            if (pid < 0) {
                perror("fork error");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                char iteration_str[10];
                snprintf(iteration_str, sizeof(iteration_str), "%d", iteration);
                execl("./user", "user", iteration_str, (char *)NULL);
                perror("execl error");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
		printf("New child process with pid %d.\n",pid); 
                processes++;
                active_process++;
            }
        } else {
            // Wait for a child process to finish
            pid_t finished_pid = wait(NULL);
            if (finished_pid > 0) {
                active_process--;
                printf("Child process %d finished.\n", finished_pid);
            } else {
                if (errno != EINTR) {
                    perror("wait error");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    // Wait for all child processes to finish
    while (active_process > 0) {
        pid_t finished_pid = wait(NULL);
        if (finished_pid > 0) {
            active_process--;
            printf("Child process %d finished.\n", finished_pid);
        } else {
            if (errno != EINTR) {
                perror("wait error");
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("All child processes have finished.\n");
    return 0;  
}

