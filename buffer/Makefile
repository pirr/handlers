CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -pedantic

test_buffer: 
	$(CC) $(CFLAGS) buffer.c ./tests/test_buffer.c -o ./tests/tests_buffer.o
	./tests/tests_buffer.o
	rm -rf ./tests/tests_buffer.o
