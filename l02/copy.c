#include "copy.h"
#include <stdio.h>
#include <errno.h>
/**
 * Copies data from intfd into outfd
 * file descriptor.
 * Returns number of copied bytes or
 * -1 on error (and leaves errno set)
 */
ssize_t copyFds(int infd, int outfd)
{
	ssize_t buffer_size = 100*1024;
	char buffer[buffer_size];
	ssize_t read_number = 0;
	ssize_t count = 0;
	ssize_t write_number = 0;
	ssize_t write_number_tmp = 0;

	for(;;) {
		read_number = read(infd, buffer, buffer_size);
		if (read_number == -1) {
			if (errno == EINTR) {
				perror("Can`t read file!");
			}
			return -1;
		}
		if (read_number == 0) {
			return count;
		}

		write_number = read_number;

		if (read_number > 0) {
			while (write_number > 0) {
				write_number_tmp = write(outfd, buffer + (read_number - write_number), write_number);
				if (write_number_tmp == -1) {
					if (errno == EINTR) {
						perror("Can`t write to the file!");
					}
				return -1;
				}
				//printf("%zd", write_number_tmp);
				write_number -= write_number_tmp;
				count += write_number_tmp;
			}
		}
	}
	return -1;
}
