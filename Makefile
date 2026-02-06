# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 22:35:31 by ilsadi            #+#    #+#              #
#    Updated: 2026/02/06 14:01:40 by amacaull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes
LIBFT_PATH  = libft
LIBFT       = $(LIBFT_PATH)/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	# === LINUX CONFIG ===
	MLX_DIR     = minilibx-linux
	MLX_REPO    = https://github.com/42Paris/minilibx-linux.git
	MLX_LIB     = $(MLX_DIR)/libmlx.a
	MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
	INCLUDES    = -I $(INC_DIR) -I $(LIBFT_PATH)/include -I $(MLX_DIR)
else
	# === MAC CONFIG ===
	MLX_DIR     = mlx
	MLX_LIB     = $(MLX_DIR)/libmlx.a
	MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
	INCLUDES    = -I $(INC_DIR) -I $(LIBFT_PATH)/include -I $(MLX_DIR)
endif

SRCS        = src/core/main.c \
			  src/core/init.c \
			  src/core/clean.c \
			  src/core/loop.c \
			  \
			  src/input/keys.c \
			  src/input/mouse.c \
			  \
			  src/parsing/parsing.c \
			  src/parsing/parsing_config.c \
			  src/parsing/parsing_validate.c \
			  src/parsing/parsing_walls.c \
			  src/parsing/parsing_utils.c \
			  src/parsing/color.c \
			  \
			  src/player/move.c \
			  src/player/utils.c \
			  src/player/stats.c \
			  \
			  src/rendering/raycasting.c \
			  src/rendering/raycast_utils.c \
			  src/rendering/textures.c \
			  src/rendering/animation.c \
			  src/rendering/background.c \
			  src/rendering/shading.c \
			  src/rendering/sprite.c \
			  \
			  src/ui/hud.c \
			  src/ui/minimap.c \
			  \
			  src/interact/door.c \
			  src/interact/collectible.c \
			  src/interact/interaction.c \
			  \
			  src/enemies/enderman.c \
			  src/enemies/enderman_render.c \
			  \
			  src/game/gameover.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

TITLE       = CUB3D
CURR_TOTAL  = $(words $(SRCS))
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
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(C_YELLOW)[INFO] MinilibX not found. Cloning $(MLX_REPO)...$(C_RESET)"; \
		git clone $(MLX_REPO) $(MLX_DIR) > /dev/null 2>&1; \
	fi
	@if [ ! -f "$(MLX_LIB)" ]; then \
		printf "$(C_YELLOW)[INFO] Compiling MinilibX...$(C_RESET)"; \
		$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1; \
		printf "\r$(CLEAR_LINE)$(C_GREEN)[INFO] MinilibX compiled successfully! ✓$(C_RESET)\n"; \
	fi
	@$(MAKE) header CURR_TOTAL=$(words $(SRCS)) --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_REPO) $(MLX_DIR) > /dev/null 2>&1; \
	fi
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@$(MAKE) footer --no-print-directory

header:
	@tput civis 2>/dev/null || true
	@echo ""
	@printf "    $(C_MAGENTA)$(C_BOLD)$(TITLE)$(C_RESET)\n"
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""
	@printf "    $(C_GRAY)Status    $(C_ORANGE)%s$(C_RESET)\n" "waiting..."
	@printf "    $(C_GRAY)Target    $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"
	@printf "    $(C_GRAY)Current   $(C_WHITE)%s$(C_RESET)\n" "..."
	@echo ""
	@printf "    $(C_GRAY)[........................................]$(C_RESET)\n"
	@echo ""
	@printf "    $(C_GRAY)Progress  $(C_WHITE)%-10s$(C_GRAY)Files  $(C_WHITE)%s$(C_RESET)\n" "0%" "0/$(CURR_TOTAL)"
	@printf "    $(C_GRAY)Warnings  $(C_GREEN)%-10s$(C_GRAY)Errors $(C_GREEN)%s$(C_RESET)\n" "0" "0"
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@tput cuu 10

footer:
	@printf "$(CLEAR_LINE)    $(C_GRAY)Status    $(C_GREEN)$(C_BOLD)%s$(C_RESET)\n" "complete ✓"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Target    $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Current   $(C_GREEN)%s$(C_RESET)\n" "done"
	@printf "$(CLEAR_LINE)\n"
	@printf "$(CLEAR_LINE)    $(C_GRAY)[$(C_GREEN)########################################$(C_GRAY)]$(C_RESET)\n"
	@printf "$(CLEAR_LINE)\n"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Progress  $(C_GREEN)%-10s$(C_GRAY)Files  $(C_GREEN)%s$(C_RESET)\n" "100%" "$(CURR_TOTAL)/$(CURR_TOTAL)"
	@printf "$(CLEAR_LINE)    $(C_GRAY)Warnings  $(C_GREEN)%-10s$(C_GRAY)Errors $(C_GREEN)%s$(C_RESET)\n" "0" "0"
	@printf "$(CLEAR_LINE)\n"
	@printf "$(CLEAR_LINE)    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""
	@tput cnorm 2>/dev/null || true

define compile_progress
	$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	$(eval PERCENT=$(shell echo $$(($(CURRENT)*100/$(CURR_TOTAL)))))
	$(eval FILLED=$(shell echo $$(($(CURRENT)*40/$(CURR_TOTAL)))))
	$(eval EMPTY=$(shell echo $$((40-$(FILLED)))))
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@BAR_FILL=$$(printf "%.*s" $(FILLED) "########################################"); \
	 BAR_EMPTY=$$(printf "%.*s" $(EMPTY) "........................................"); \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Status    $(C_ORANGE)%s$(C_RESET)\n" "compiling"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Target    $(C_WHITE)%s$(C_RESET)\n" "$(NAME)"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Current   $(C_YELLOW)%s$(C_RESET)\n" "$(notdir $<)"; \
	 printf "$(CLEAR_LINE)\n"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)[$(C_MAGENTA)%-40s$(C_GRAY)]$(C_RESET)\n" "$$BAR_FILL$$BAR_EMPTY"; \
	 printf "$(CLEAR_LINE)\n"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Progress  $(C_WHITE)%-10s$(C_GRAY)Files  $(C_WHITE)%s$(C_RESET)\n" "$(PERCENT)%" "$(CURRENT)/$(CURR_TOTAL)"; \
	 printf "$(CLEAR_LINE)    $(C_GRAY)Warnings  $(C_GREEN)%-10s$(C_GRAY)Errors $(C_GREEN)%s$(C_RESET)\n" "0" "0"; \
	 printf "$(CLEAR_LINE)\n"; \
	 tput cuu 9
endef

$(OBJ_DIR)/%.o: %.c
	@$(call compile_progress)

clean:
	@make clean -C $(LIBFT_PATH) --no-print-directory
	@if [ -d "$(MLX_DIR)" ]; then make clean -C $(MLX_DIR) > /dev/null 2>&1; fi
	@rm -rf $(OBJ_DIR)
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@printf "    $(C_ORANGE)✗ $(C_GRAY)Cleaned $(C_WHITE)cub3D $(C_GRAY)objects$(C_RESET)\n"
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""

fclean:
	@make fclean -C $(LIBFT_PATH) --no-print-directory
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@printf "    $(C_ORANGE)✗ $(C_GRAY)Cleaned $(C_WHITE)cub3D $(C_GRAY)objects$(C_RESET)\n"
	@printf "    $(C_ORANGE)✗ $(C_GRAY)Removed $(C_WHITE)$(NAME)$(C_RESET)\n"
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""

re: fclean all

norm:
	@echo ""
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@printf "    $(C_MAGENTA)Norminette $(C_GRAY)%s$(C_RESET)\n" "checking..."
	@if norminette $(SRC_DIR) $(INC_DIR) | grep -q "Error"; then \
		printf "    $(C_ORANGE)Errors found!$(C_RESET)\n"; \
		norminette $(SRC_DIR) $(INC_DIR) | grep "Error"; \
	else \
		printf "    $(C_GREEN)All clear ✓$(C_RESET)\n"; \
	fi
	@printf "    $(C_CYAN)──────────────────────────────────────────$(C_RESET)\n"
	@echo ""

.PHONY: all clean fclean re norm header footer
