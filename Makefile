# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 22:35:31 by ilsadi            #+#    #+#              #
#    Updated: 2026/01/22 22:35:32 by ilsadi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     =	cub3d

LIBFT = libft/libft.a

DIR 	 =      src/

SRC	     =		src/main.c	 \
 				src/clean.c \
				src/handle_keys.c \
				src/init_game.c \
				src/parsing/parsing.c \
				src/parsing/cub_config.c \
				src/parsing/parse_utils.c \
				src/parsing/color.c


CC       =	    cc

CFLAGS   =	    -Wall -Wextra -Werror -g3 -I./inc -Imlx

OBJ_DIR	 =	    obj/

SRCS     =      $(SRC)

OBJ 	 =      $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =      mkdir -p

SMAKE	 =      make --no-print-directory

MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

MLX_DIR = ./mlx

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

MLX_FLAGS = -L $(MLX_DIR) -lmlx_Linux -L /usr/X11/lib -lXext -lX11 -lm

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(YELLOW)[INFO] MinilibX not found, cloning...$(RESET)"; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@echo "$(YELLOW)[INFO] Compiling MinilibX...$(RESET)"
	@make -C $(MLX_DIR)

$(OBJ_DIR)%.o:  src/%.c
				@$(MAKE_DIR) $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@

all:	        $(NAME)

libft/libft.a:
	@$(MAKE) -C libft --no-print-directory

$(NAME):        $(OBJ) $(LIBFT) $(MLX_LIB)
				@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $@

clean:
				@rm -rf $(OBJ_DIR)
				@make -C libft clean --no-print-directory
				@echo "\033[1;31m======== object files removed ========\033[0m"

fclean:         clean
				@$(RM) $(NAME)
				@make -C libft fclean --no-print-directory
				@rm -rf minilibx-linux
				@echo "\033[1;31m======== executable removed  =======\033[0m"

re:             fclean all

.PHONY: clean fclean all re