# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/07/09 12:00:21 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= miniRT

CC				:= cc
COMPILE_FLAGS	:= -Wall -Wextra -Werror
MLX_FLAGS		:= -Iinclude -ldl -lglfw -pthread -lm
# ---------------------------------------------------------------------------- #
DEBUG_FLAGS := -g
# ---------------------------------------------------------------------------- #
LIBFT_DIR := libft_plus
LIBFT_LIB := $(LIBFT_DIR)/libft_plus.a
# ---------------------------------------------------------------------------- #
MLX_REPO		:= https://github.com/codam-coding-college/MLX42.git
MLX_DIR			:= MLX42
MLX_BUILD_DIR	:= $(MLX_DIR)/build
MLX_LIB			:= $(MLX_BUILD_DIR)/libmlx42.a
# ---------------------------------------------------------------------------- #
SRC_DIR	:=	src
SRC		:=	main.c									\
			image_to_file.c							\
			initialization_01.c						\
			memory/free_memory.c					\
			memory/dealloc_linked_lists.c			\
			parsing/elems/parse_cam_and_lights.c	\
			parsing/elems/parse_shapes.c			\
			parsing/parse_scene.c					\
			parsing/parse_segment.c					\
			parsing/parse_value.c					\
			parsing/utils.c							\
			utils/errors.c							\
			utils/utils_01.c						\
			utils/utils_02.c						\
			vectors/vectors_01.c					\
			vectors/vectors_02.c					\
			matrices/matrices_01.c					\
			matrices/matrices_02.c					\
			matrices/matrices_03.c					\
			matrices/transforms_01.c				\
			rays/rays_01.c							\
			color/colors_01.c						\
			color/backgrounds_01.c					\
			objects/sphere_intersection.c			\
			objects/materials_01.c					\
			objects/transform_initialization.c		\
			intersections/intersections_01.c		\
			lighting/lighting_01.c					\
			lighting/single_sphere.c
# ---------------------------------------------------------------------------- #
INC_DIR			:= inc
INC_FILES		:= minirt.h settings.h
HEADERS			:= $(INC_FILES:%=$(INC_DIR)/%)
COMPILE_FLAGS	+= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include \
				   -I$(MLX_DIR)/include/MLX42
# ---------------------------------------------------------------------------- #
OBJ_DIR		:= obj
OBJ			:= $(SRC:%.c=$(OBJ_DIR)/%.o)
.SECONDARY	:= $(OBJ)
# ---------------------------------------------------------------------------- #
.DEFAULT = all

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(COMPILE_FLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(COMPILE_FLAGS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR) -s --no-print-directory

$(MLX_LIB):
	if ! find . -maxdepth 1 -type d | grep MLX42; then\
		git clone $(MLX_REPO) $(MLX_DIR);\
	fi;
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

# ---------------------------------------------------------------------------- #

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	rm -rf $(NAME)

re: fclean all

neat: all clean
	clear

# ---------------------------------------------------------------------------- #
debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re
# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re neat debug
# ---------------------------------------------------------------------------- #
