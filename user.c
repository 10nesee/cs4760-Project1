#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int iterations = atoi(argv[1]);
	printf("iterations=%d\n", iterations);
	return 0;
}
