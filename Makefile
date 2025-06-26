# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/06/25 17:03:28 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

INC_DIR := inc
INC_FILES := minirt.h

LIBFT_DIR := libft_plus
LIBFT_LIB := $(LIBFT_DIR)/libft_plus.a

CC := cc
COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include
COMPILE_WITH_MLX := $(MLX_LIB) -Iinclude -ldl -lglfw -pthread -lm

DEBUG_FLAGS := -g

MLX_REPO := https://github.com/codam-coding-college/MLX42.git
MLX_DIR := MLX42
MLX_BUILD_DIR := $(MLX_DIR)/build
MLX_LIB := $(MLX_BUILD_DIR)/libmlx42.a

SRC_DIR := src
SRC_FILES := main.c \
			 errors.c \
			 memory/free_memory.c \
			 memory/dealloc_linked_lists.c \
			 parsing/elems/parse_cam_and_lights.c \
			 parsing/elems/parse_shapes.c \
			 parsing/parse_scene.c \
			 parsing/parse_segment.c \
			 parsing/parse_value.c \
			 parsing/utils.c

OBJ_DIR := obj

OBJ := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
HEADERS := $(INC_FILES:%=$(INC_DIR)/%)

.SECONDARY = $(OBJ)
.DEFAULT = all
all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

$(MLX_LIB):
	if ! find . | grep MLX42; then \
		git clone $(MLX_REPO) $(MLX_DIR);\
	fi;
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ) $(HEADERS)
	$(CC) $(COMPILE_FLAGS) $(OBJ) $(LIBFT_LIB) $(COMPILE_WITH_MLX) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory

re: fclean all

neat: $(NAME) clean
	clear
# ---------------------------------------------------------------------------- #
debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re
# ---------------------------------------------------------------------------- #

.PHONY: all bonus clean fclean re neat debug
