# rules
all: test

clean:
	rm a.out

test:
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=10000000 -I get_next_line main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
	./a.out

bonus:
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=10000000 -I get_next_line main.c get_next_line/get_next_line_bonus.c get_next_line_utils_bonus.c
	./a.out

.PHONY: all test clean bonus