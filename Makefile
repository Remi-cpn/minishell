# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: von <von@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/07 09:56:21 by rcompain          #+#    #+#              #
#    Updated: 2026/03/08 15:17:12 by von              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g 
LDFLAGS		= -lreadline
RM			= rm -f
AR			= ar rcs

# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/test.c \
			  $(SRC_DIR)/init/init.c \
			  $(SRC_DIR)/init/init_minimal_env.c \
			  $(SRC_DIR)/exit/exit.c \
			  $(SRC_DIR)/exit/free.c \
			  $(SRC_DIR)/exit/exit_utils.c \
			  $(SRC_DIR)/signals/init_signals.c \
			  $(SRC_DIR)/expand/expand.c \
			  $(SRC_DIR)/expand/expand_logic.c \
			  $(SRC_DIR)/expand/expand_dispatch.c \
			  $(SRC_DIR)/expand/expand_heredoc.c \
			  $(SRC_DIR)/expand/split.c \
			  $(SRC_DIR)/expand/?.c \
			  $(SRC_DIR)/expand/wildcard.c \
			  $(SRC_DIR)/expand/wildcard_arg.c \
			  $(SRC_DIR)/expand/wildcard_utils.c \
			  $(SRC_DIR)/builtins/cd.c \
			  $(SRC_DIR)/builtins/echo.c \
			  $(SRC_DIR)/builtins/env.c \
			  $(SRC_DIR)/builtins/exit.c \
			  $(SRC_DIR)/builtins/export.c \
			  $(SRC_DIR)/builtins/export_not_args.c \
			  $(SRC_DIR)/builtins/pwd.c \
			  $(SRC_DIR)/builtins/unset.c \
			  $(SRC_DIR)/builtins/utils.c \
			  $(SRC_DIR)/parser/lookup.c \
			  $(SRC_DIR)/parser/parse_utils.c \
			  $(SRC_DIR)/parser/parse_args.c \
			  $(SRC_DIR)/parser/parser.c \
			  $(SRC_DIR)/lexer/lexer.c \
			  $(SRC_DIR)/lexer/lexer_utils.c \
			  $(SRC_DIR)/lexer/word.c \
			  $(SRC_DIR)/pipeline/open.c \
			  $(SRC_DIR)/pipeline/heredoc.c \
			  $(SRC_DIR)/pipeline/exec_one_cmd.c \
			  $(SRC_DIR)/pipeline/exec_pipeline.c \
			  $(SRC_DIR)/pipeline/exec.c \
			  $(SRC_DIR)/pipeline/init_cmds.c \
			  $(SRC_DIR)/pipeline/find_path.c \
			  $(SRC_DIR)/pipeline/utils.c
			  

OBJ			= ${SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o}

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: banner $(LIBFT_A) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) $(LDFLAGS) $(LIBFT_A) -o $(NAME)
	@echo "\r\033[2K$(CYAN)📝 Compiled project files: $(BOLD)$(GREEN)[OK]$(RESET)"
	@echo "$(BOLD) $(GREEN)\n         Project compiled successfully ✅$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiled project files: %s$(RESET)" "$<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)
	@echo "\r\033[2K$(CYAN)📚 Compiled library files: $(BOLD)$(GREEN)[OK]$(RESET)"

clean:
	@make clean -s -C $(LIBFT_DIR)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(CYAN)Object files removed$(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(CYAN)Executable removed$(RESET)"

re: fclean all

# **************************************************************************** #
#                                   DECO & COLORS                              #
# **************************************************************************** #

GREEN		= \033[32m
CYAN		= \033[36m
ORANGE  = \033[38;5;214m
RESET		= \033[0m

BOLD		=\033[1m

BANNER = \
"$(BOLD)$(ORANGE)\n\n  	          Compilation ...  $(RESET)\n"\

banner:
	@echo $(BANNER)

.PHONY: all clean fclean re banner

