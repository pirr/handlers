CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -pedantic

test_request:
	$(CC) $(CFLAGS) ../buffer/buffer.c ../url/url.c request.c ./tests/test_request.c -O -o ./tests/test_request.o
	./tests/test_request.o
	rm -rf ./tests/*.o ./tests/*.dSYM
