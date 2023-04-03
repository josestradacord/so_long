# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 11:55:14 by joestrad          #+#    #+#              #
#    Updated: 2023/03/30 11:45:35 by joestrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)

GNL_DIR = gnl
SRC_GNL = $(wildcard $(GNL_DIR)/*.c)
GNL_OBJS = $(SRC_GNL:.c=.o) 

OBJS = $(SRCS:.c=.o)

# Bonus part
NAME_BONUS = so_long_bonus
SRC_BONUS_DIR = src_bonus
SRCS_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INC_LFT = -Ilibft
LIBFT = libft/libft.a
LIBFT_D = libft

MLX_DIR = MLX42
LIBMLXL = libmlx42.a
LIBMLX = $(MLX_DIR)/libmlx42.a -ldl -lglfw -pthread -lm
INC_MLX = -I$(MLX_DIR)/include/MLX42 -Iinclude -lglfw -L"/Users/$$USER/.brew/opt/glfw/lib/"

HEADERS = -Iinclude $(INC_LFT)

INC = $(HEADERS) $(INC_MLX)

CC = gcc
FLAGS = -Wall -Werror -Wextra

RM = rm -f

GREEN = "\033[32m"
VIOLET = "\033[35m"
YELLOW = "\033[33m"
RED = "\033[31m"
NOCOLOR = "\033[0m"

all: $(LIBFT) $(LIBMLXL) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS)
	@echo $(YELLOW)Norminette...$(NOCOLOR)
	@norminette src
	@$(CC) $(FLAGS) $(INC) $(LIBMLX) $(LIBFT) $(SRCS) $(SRC_GNL) -o $(NAME)
	@echo $(GREEN)Program $(NAME) ready$(NOCOLOR)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

gnl:
	@$(CC) $(FLAGS) -c $(SRC_GNL)

$(LIBMLXL):
	@echo $(VIOLET)Lib MLX42 compilation...$(NOCOLOR)
	@make -C $(MLX_DIR) --silent
	@echo $(GREEN)Library MLX42 ready$(NOCOLOR)

bonus: $(LIBFT) $(LIBMLXL) $(NAME_BONUS)

$(LIBFT):
	@echo $(VIOLET)Libft compilation...$(NOCOLOR)
	@make -C $(LIBFT_D) --silent
	@make bonus -C $(LIBFT_D) --silent
	@echo $(GREEN)Libft ready$(NOCOLOR)

$(NAME_BONUS): $(OBJS_BONUS) $(GNL_OBJS)
	@echo $(YELLOW)Norminette...$(NOCOLOR)
	@norminette src_bonus
	@$(CC) $(FLAGS) $(INC) $(LIBMLX) $(LIBFT) $(SRCS_BONUS) $(SRC_GNL) -o $(NAME_BONUS)
	@echo $(GREEN)Program $(NAME_BONUS) ready$(NOCOLOR)


clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)
	@$(RM) $(GNL_DIR)/get_next_line.o
	@make clean -C $(MLX_DIR) --silent
	@make clean -C libft --silent
	@echo Objects files $(RED)cleaned$(NOCOLOR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@$(RM) $(LIBFT)
	@echo Executables files $(RED)cleaned$(NOCOLOR)

re: fclean all
	@echo $(RED)Cleaned$(NOCOLOR) and $(GREEN)rebuilt$(NOCOLOR) $(NAME) project

re_bonus: fclean bonus
	@echo $(RED)Cleaned$(NOCOLOR) and $(GREEN)rebuilt$(NOCOLOR) $(NAME_BONUS) project

.PHONY: all clean fclean re re_bonus