NAME = cub3D

CC = gcc
LINKER = gcc
CFLAGS = -Wall -Wextra -Werror -Wall -I/usr/include -Imlx_linux -O3
LFLAGS = -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRCS = main.c errors.c get_map_data.c ft_strtoitab.c \
		check_mapdata.c check_mapdata_2.c pathfinder.c \
		tools_1.c print_map.c \
		windows_management.c
		#play_level.c \

MY_PROJECT_BASE_DIRECTORY = /mnt/c/Users/user/Documents/_42/plusTard/cub3D
SRCDIR = src
OBJDIR = obj
BINDIR = bin
MLXDIR = MLXXXXXXXXXXXXXXXX for windows

LIBRARIES =  $(SRCDIR)/libft.a $(MLXDIR)/libmlx.a #$(MLXDIR)/libmlx_x86_64.a

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(NAME): $(OBJS)
	$(LINKER) $(OBJS) -o $@ $(LFLAGS) $(LIBRARIES)
	@echo "Linking complete!"

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"


#$(NAME): $(OBJS) cub3D.h
#	gcc -o $(NAME) $(OBJS) inc/libft.a inc/libmlx.a -lm -lXext -lX11
#
#all: $(NAME)

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: fclean
fclean: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

re: fclean all

.PHONY: all re