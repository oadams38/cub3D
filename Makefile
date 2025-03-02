NAME = cub3D

DIR_LIBFT	= libft/
DIR_SRCS	= srcs/
DIR_MATH	= math/
DIR_MINILIB	= minilib/
DIR_PARSING	= parsing/
DIR_UTILS	= utils/
DIR_MAP		= map/

SRCS_BONUS = 	main.c \
		$(DIR_MATH)dda.c \
		$(DIR_MATH)draw.c \
		$(DIR_MATH)move.c \
		$(DIR_MATH)vector_operations.c \
		$(DIR_MINILIB)events.c \
		$(DIR_MINILIB)loop.c \
		$(DIR_PARSING)parsing_main.c \
		$(DIR_PARSING)parsing_map1.c \
		$(DIR_PARSING)parsing_map2.c \
		$(DIR_PARSING)parsing_texture.c \
		$(DIR_PARSING)parsing_utils.c \
		$(DIR_UTILS)clear_utils.c \
		$(DIR_MAP)map_main.c \
		$(DIR_MAP)map_bresenham.c \
		$(DIR_MAP)map_utils.c \
		$(DIR_UTILS)clear.c \
		$(DIR_UTILS)error.c \
		$(DIR_UTILS)init.c \
		$(DIR_UTILS)utils.c 


PATH_SRCS	= $(addprefix $(DIR_SRCS), $(SRCS))
OBJS 		= $(PATH_SRCS:.c=.o)

INCLUDES = includes/cub3d.h includes/cub3d.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LDFLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(DIR_LIBFT)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) $(LDFLAGS)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(DIR_LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(DIR_LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
