CFLAGS = -Werror -Wextra -Wall -MMD -g3 -fPIC
INCLUDES = -Iincludes -I./lib/libft/includes -I./minilibx-linux
SRC_DIR = src
OBJ_DIR = objs
MLX = minilibx-linux
MLXFLAGS = -L$(MLX) -lmlx -lXext -lX11 -lm
LIBFT = lib/libft/lib/libft.a

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPENDS = $(OBJS:.o=.d)

NAME = cub3D

-include $(DEPENDS)

.PHONY: all clean fclean re

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C $(MLX)
	$(CC) $^ -o $@ $(MLXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C lib/libft

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX)
	$(MAKE) -C lib/libft clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C lib/libft fclean

re: fclean all
