NAME=jpeg_encoder
CC=gcc
GFLAGS = -Werror -Wextra -Wall
COM=
LIB= -Llibft -lft
SRCS = main.c \
		bmp/bmp.c \
		bmp/bmp_header.c \
		bmp/bmp_info_header.c \
		bmp/bmp_display_format.c \
		bmp/bmp_image_data.c \

OBJS = $(SRCS:%.c=%.o)

%.o:%.c
	@$(CC) $(GFLAGS) $< -c -o $@

$(NAME): $(OBJS)
	@$(CC)  $(OBJS) $(LIB) -o $(NAME)


run: $(NAME)
	@ valgrind -s --log-file=valgrind --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME) $(IMG_PATH)
clean:
	rm -f $(OBJS)
	rm -f valgrind

fclean: clean
	rm -f $(NAME)
	rm -f image/raw_data

git: fclean
	git add .
	git commit -m $(COM)
	git push origin main