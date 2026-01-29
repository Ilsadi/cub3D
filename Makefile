# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 22:35:31 by ilsadi            #+#    #+#              #
#    Updated: 2026/01/29 23:36:57 by amacaull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LIBFT_DIR   = libft
MLX_DIR     = mlx
LIBFT       = $(LIBFT_DIR)/libft.a

# Mac
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm

#Linux
# MLX_FLAGS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
# MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
# MLX_DIR = ./mlx
# MLX_REPO = https://github.com/42Paris/minilibx-linux.git
# $(MLX_LIB):
# 	@if [ ! -d "$(MLX_DIR)" ]; then \
# 		echo "$(YELLOW)[INFO] MinilibX not found, cloning...$(RESET)"; \
# 		git clone $(MLX_REPO) $(MLX_DIR); \
# 	fi
# 	@echo "$(YELLOW)[INFO] Compiling MinilibX...$(RESET)"
# 	@make -C $(MLX_DIR)

INCLUDES    = -I$(LIBFT_DIR)/include -Iincludes -I$(MLX_DIR)

SRCS        = src/game/main.c \
              src/game/init.c \
              src/game/clean.c \
              src/game/keys.c \
              src/game/game_loop.c \
              src/game/player.c \
              src/parsing/parsing.c \
              src/parsing/parsing_config.c \
              src/parsing/parsing_validate.c \
              src/parsing/parsing_walls.c \
              src/parsing/parsing_utils.c \
              src/parsing/color.c \
              src/rendering/raycasting.c \
              src/rendering/textures.c \
              src/rendering/minimap.c \
              src/rendering/floor_ceiling.c

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
