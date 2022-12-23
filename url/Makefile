CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -pedantic

test_url:
	$(CC) $(CFLAGS) url.c ../buffer/buffer.c ./tests/test_url.c -o ./tests/test_url.o
	./tests/test_url.o
	rm -rf ./tests/test_url.o
