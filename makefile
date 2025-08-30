NAME=jpeg_encoder
CC=gcc
GFLAGS = -Werror -Wextra -Wall
COM=
SRCS = main.c \
		bmp/*.c \

OBJS = $(SRCS:%.c=%.o)

%.o:%.c
	@$(CC) $(GFLAGS) $< -c -o $@

$(NAME): $(OBJS)
	@$(CC)  $(OBJS) -o $(NAME)

run: $(NAME)
	@ valgrind --log-file=valgrind --leak-check=full --track-fds=all ./$(NAME)

clean:
	rm -f $(OBJS)
	rm -f valgrind

fclean: clean
	rm -f $(NAME)

git: fclean
	git add .
	git commit -m $(COM)
	git push origin main