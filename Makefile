NAME = so_long
SRC = so_long.c map.c handle_input.c checkpath.c render.c close_game.c parsemap.c
LIBFT_DIR = ./libft

OBJ := $(SRC:%.c=%.o)
GNL_OBJ := $(GNL_SRC:%.c=%.o)
PRINTF_OBJ := $(PRINTF_SRC:%.c=%.o)

CC = cc
CCFLAGS = -Wextra -Wall -Werror -lmlx -lX11 -lXext -L./libft -lft -g

all: $(NAME)

$(NAME): $(OBJ) libft
	$(CC)  $(OBJ) $(CCFLAGS) -o $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	make clean
	rm -f $(NAME)

re : fclean all clean

.PHONY : all clean fclean libft
