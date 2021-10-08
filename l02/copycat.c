#include "copy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
	int infd = 0; // standard input
	int outfd = 1; // standard output

	if (argc > 1) {
		if (argc != 3) {
			fprintf(stderr, "Error: copycat needs either no or exactly two arguments!\n");
			// This is basically the same as `return EXIT_FAILURE` here,
			// since we are in main.
			exit(EXIT_FAILURE);
		}

		if (strcmp("-", argv[1])) {
			infd = open(argv[1], O_RDONLY);
			if (infd == -1) {
				perror("Error: input file can`t be opened!\n");
				exit(EXIT_FAILURE);
			}

		}
		if (strcmp("-", argv[2])) {
			outfd = open(argv[2], (O_RDWR | O_CREAT), 0777);
			if (outfd == -1) {
				close(infd);
				perror("Error: output file can`t be opened!\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	if (copyFds(infd, outfd) == -1) {
		perror("Error copying");
		return EXIT_FAILURE;
	}

	close(infd);
	close(outfd);
	
	return EXIT_SUCCESS;
}
