NAME = so_long
SRC = so_long.c map.c handle_input.c checkpath.c render.c close_game.c
LIBFT_DIR = ./libft
GNL_SRC = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
PRINTF_SRC = $(addprefix printf/, ft_printf.c ft_print.c ft_numbers.c )

OBJ := $(SRC:%.c=%.o)
GNL_OBJ := $(GNL_SRC:%.c=%.o)
PRINTF_OBJ := $(PRINTF_SRC:%.c=%.o)

CC = cc
CCFLAGS = -Wextra -Wall -Werror -lmlx -lX11 -lXext -L./libft -lft -g

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJ) $(PRINTF_OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(CCFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CCFLAGS)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ) $(GNL_OBJ) $(PRINTF_OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	make clean
	rm -f $(NAME)

re : fclean all clean
