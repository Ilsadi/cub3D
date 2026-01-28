# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/15 09:51:54 by amacaull          #+#    #+#              #
#    Updated: 2025/12/02 13:07:49 by amacaull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c \
       parse_bonus_flags.c \
       dispatcher.c \
       print_char_str.c \
       print_int_unsigned.c \
       print_hex_ptr.c \
       ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

INCS = -I .

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	@ar rcs $(NAME) $(OBJS_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
