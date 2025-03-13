# rules
all: test

clean:
	rm a.out
	rm bonus

test:
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I get_next_line main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
	norminette -R CheckForbiddenSourceHeader ./get_next_line
	valgrind ./a.out

bonus:
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I get_next_line main_bonus.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c -o bonus
	valgrind ./bonus

.PHONY: all test clean bonus
