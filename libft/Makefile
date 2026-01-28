# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 13:02:28 by amacaull          #+#    #+#              #
#    Updated: 2026/01/28 09:30:16 by amacaull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I include

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = src/libft/ft_atoi.c \
   			  src/libft/ft_bzero.c \
 			  src/libft/ft_calloc.c \
		      src/libft/ft_isalnum.c \
  			  src/libft/ft_isalpha.c \
  			  src/libft/ft_isascii.c \
  			  src/libft/ft_isdigit.c \
  			  src/libft/ft_isprint.c \
  			  src/libft/ft_itoa.c \
  			  src/libft/ft_lstadd_back.c \
  			  src/libft/ft_lstadd_front.c \
  			  src/libft/ft_lstclear.c \
  			  src/libft/ft_lstdelone.c \
  			  src/libft/ft_lstiter.c \
  			  src/libft/ft_lstlast.c \
  			  src/libft/ft_lstmap.c \
  			  src/libft/ft_lstnew.c \
  			  src/libft/ft_lstsize.c \
  			  src/libft/ft_memchr.c \
			  src/libft/ft_memcmp.c \
    		  src/libft/ft_memcpy.c \
    		  src/libft/ft_memmove.c \
    		  src/libft/ft_memset.c \
    		  src/libft/ft_putchar_fd.c \
    		  src/libft/ft_putendl_fd.c \
    		  src/libft/ft_putnbr_fd.c \
    		  src/libft/ft_putstr_fd.c \
    		  src/libft/ft_split.c \
    		  src/libft/ft_strchr.c \
    		  src/libft/ft_strdup.c \
    		  src/libft/ft_striteri.c \
    		  src/libft/ft_strjoin.c \
    		  src/libft/ft_strlcat.c \
    		  src/libft/ft_strlcpy.c \
    		  src/libft/ft_strlen.c \
    		  src/libft/ft_strmapi.c \
    		  src/libft/ft_strncmp.c \
    		  src/libft/ft_strnstr.c \
    		  src/libft/ft_strrchr.c \
    		  src/libft/ft_strtrim.c \
    		  src/libft/ft_substr.c \
    		  src/libft/ft_tolower.c \
    		  src/libft/ft_toupper.c \
			  src/libft/ft_free_tab.c \
			  src/gnl/get_next_line_clear.c \
    		  src/gnl/get_next_line_utils.c \
  			  src/gnl/get_next_line.c \
    		  src/printf/dispatcher.c \
    		  src/printf/ft_printf_utils.c \
    		  src/printf/ft_printf.c \
    		  src/printf/parse_bonus_flags.c \
    		  src/printf/print_char_str.c \
    		  src/printf/print_hex_ptr.c \
    		  src/printf/print_int_unsigned.c \

OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TOTAL_FILES = $(words $(SRCS))
CURRENT     = 0

C_CYAN      = \033[38;5;51m
C_MAGENTA   = \033[38;5;198m
C_YELLOW    = \033[38;5;226m
C_GREEN     = \033[38;5;46m
C_ORANGE    = \033[38;5;208m
C_WHITE     = \033[38;5;255m
C_GRAY      = \033[38;5;244m
C_RESET     = \033[0m
C_BOLD      = \033[1m
CLEAR_LINE  = \033[2K

all:
	@if $(MAKE) -q $(NAME) --no-print-directory 2>/dev/null; then \
		echo ""; \
		printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"; \
		printf "    $(C_GREEN)✓ $(C_WHITE)$(NAME) $(C_GRAY)is up to date$(C_RESET)\n"; \
		printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"; \
		echo ""; \
	else \
		$(MAKE) header --no-print-directory; \
		$(MAKE) $(NAME) --no-print-directory; \
		$(MAKE) footer --no-print-directory; \
	fi

header:
	@tput civis 2>/dev/null || true
	@echo ""
	@printf "    $(C_MAGENTA)$(C_BOLD)LIBFT$(C_RESET)\n"
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""
	@printf "    $(C_GRAY)Status    $(C_ORANGE)%s$(C_RESET)\n" "waiting..."
	@printf "    $(C_GRAY)Target    $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"
	@printf "    $(C_GRAY)Current   $(C_WHITE)%s$(C_RESET)\n" "..."
	@echo ""
	@printf "    $(C_GRAY)[........................................]$(C_RESET)\n"
	@echo ""
	@printf "    $(C_GRAY)Progress  $(C_WHITE)%-10s$(C_GRAY)Files  $(C_WHITE)%s$(C_RESET)\n" "0%" "0/$(TOTAL_FILES)"
	@printf "    $(C_GRAY)Warnings  $(C_GREEN)%-10s$(C_GRAY)Errors $(C_GREEN)%s$(C_RESET)\n" "0" "0"
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@tput cuu 10

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

footer:
	@printf "$(CLEAR_LINE)    $(C_GRAY)Status    $(C_GREEN)$(C_BOLD)%s$(C_RESET)\n" "complete ✓"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Target    $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Current   $(C_GREEN)%s$(C_RESET)\n" "done"
	@printf "$(CLEAR_LINE)\n"
	@printf "$(CLEAR_LINE)    $(C_GRAY)[$(C_GREEN)########################################$(C_GRAY)]$(C_RESET)\n"
	@printf "$(CLEAR_LINE)\n"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Progress  $(C_GREEN)%-10s$(C_GRAY)Files  $(C_GREEN)%s$(C_RESET)\n" "100%" "$(TOTAL_FILES)/$(TOTAL_FILES)"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Warnings  $(C_GREEN)%-10s$(C_GRAY)Errors $(C_GREEN)%s$(C_RESET)\n" "0" "0"
	@printf "$(CLEAR_LINE)\n"
	@printf "$(CLEAR_LINE)    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""
	@tput cnorm 2>/dev/null || true

define compile_progress
	$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	$(eval PERCENT=$(shell echo $$(($(CURRENT)*100/$(TOTAL_FILES)))))
	$(eval FILLED=$(shell echo $$(($(CURRENT)*40/$(TOTAL_FILES)))))
	$(eval EMPTY=$(shell echo $$((40-$(FILLED)))))
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@BAR_FILL=$$(printf "%.*s" $(FILLED) "########################################"); \
	 BAR_EMPTY=$$(printf "%.*s" $(EMPTY) "........................................"); \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Status    $(C_ORANGE)%s$(C_RESET)\n" "compiling"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Target    $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Current   $(C_YELLOW)%s$(C_RESET)\n" "$(notdir $<)"; \
	 printf "$(CLEAR_LINE)\n"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)[$(C_MAGENTA)%-40s$(C_GRAY)]$(C_RESET)\n" "$$BAR_FILL$$BAR_EMPTY"; \
	 printf "$(CLEAR_LINE)\n"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Progress  $(C_WHITE)%-10s$(C_GRAY)Files  $(C_WHITE)%s$(C_RESET)\n" "$(PERCENT)%" "$(CURRENT)/$(TOTAL_FILES)"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Warnings  $(C_GREEN)%-10s$(C_GRAY)Errors $(C_GREEN)%s$(C_RESET)\n" "0" "0"; \
	 printf "$(CLEAR_LINE)\n"; \
	 tput cuu 9
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call compile_progress)

clean:
	@rm -rf $(OBJ_DIR)
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@printf "    $(C_ORANGE)✗ $(C_GRAY)%s$(C_RESET)\n" "Cleaned libft objects"
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@printf "    $(C_ORANGE)✗ $(C_GRAY)%s$(C_RESET)\n" "Cleaned libft objects"
	@printf "    $(C_ORANGE)✗ $(C_GRAY)Removed $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""

re: fclean all

norm:
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@printf "    $(C_MAGENTA)Norminette $(C_GRAY)%s$(C_RESET)\n" "checking..."
	@if norminette $(SRC_DIR) include | grep -q "Error"; then \
		printf "    $(C_ORANGE)Errors found!$(C_RESET)\n"; \
		norminette $(SRC_DIR) include | grep "Error"; \
	else \
		printf "    $(C_GREEN)All clear ✓$(C_RESET)\n"; \
	fi
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""

.PHONY: all clean fclean re header footer norm
