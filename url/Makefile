CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -pedantic

test_url:
	$(CC) $(CFLAGS) ../buffer/buffer.c ./url.c ./tests/test_url.c -v -O -o ./tests/test_url.o
	./tests/test_url.o
	rm -rf ./tests/*.o ./tests/*.dSYM
