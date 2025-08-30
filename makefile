NAME=jpeg_encoder
CC=gcc
GFLAGS = -Werror -Wextra -Wall

SRCS = main.c \
		bmp/*.c \

OBJS = $(SRCS:%.c=%.o)

%.o:%.c
	$(CC) $(GFLAGS) $< -c -o $@

$(NAME): $(OBJS)
	@$(CC)  $(OBJS) -o $(NAME)

run: $(NAME)
	@./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)