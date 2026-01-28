# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 22:35:31 by ilsadi            #+#    #+#              #
#    Updated: 2026/01/28 10:13:26 by amacaull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= libft
MLX_DIR		= mlx

LIBFT		= $(LIBFT_DIR)/libft.a

# Mac
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm

# Linux
# MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES	= -I$(LIBFT_DIR)/include -Iincludes -I$(MLX_DIR)

SRCS		= src/game/main.c \
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
			  src/rendering/raycasting.c

OBJS		= $(SRCS:.c=.o)

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
