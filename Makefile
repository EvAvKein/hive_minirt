# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/08/12 15:44:18 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= miniRT

CC					:= cc
COMPILE_FLAGS		:= -Wall -Wextra -Werror
MLX_FLAGS			:= -Iinclude -ldl -lglfw -pthread -lm
# ---------------------------------------------------------------------------- #
OPTIMIZATION_FLAGS	:= -O3 -ffast-math -flto -march=native
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
			screenshot/image_to_file.c				\
			screenshot/get_available_file_name.c	\
			ui/hooks_01.c							\
			ui/hooks_02.c							\
			init/obj_initialization.c				\
			init/mlx_initialization.c				\
			init/asset_initialization.c				\
			init/pixel_and_misc_initialization.c	\
			memory/free_memory.c					\
			memory/dealloc_linked_lists.c			\
			parsing/elems/cam_and_lights_parse.c	\
			parsing/elems/sphere_parse.c			\
			parsing/elems/plane_parse.c				\
			parsing/elems/cylinder_parse.c			\
			parsing/elems/triangle_parse.c			\
			parsing/parse_scene.c					\
			parsing/parse_segment.c					\
			parsing/parse_value.c					\
			parsing/parse_pattern.c					\
			parsing/utils/range_checks.c			\
			parsing/utils/char_checks_and_skips.c	\
			utils/errors.c							\
			utils/utils_01.c						\
			utils/utils_02.c						\
			vectors/vectors_01.c					\
			vectors/vectors_02.c					\
			vectors/vectors_03.c					\
			matrices/base_matrices.c				\
			matrices/utility_matrices.c				\
			matrices/print_m4x4.c					\
			matrices/transform_matrices.c			\
			rays/rays_01.c							\
			rays/cast_rays.c						\
			rays/ray_at_obj.c						\
			rays/ray_at_cone.c						\
			color/colors_01.c						\
			color/uv_mapping.c						\
			color/mat_by_texture.c					\
			color/backgrounds_01.c					\
			color/patterns.c						\
			color/obj_pattern_mats.c				\
			color/pattern_checkerboard.c			\
			color/material_at_pos_of_obj.c			\
			objects/sphere_intersection.c			\
			objects/plane_intersection.c			\
			objects/cylinder_intersection.c			\
			objects/cone_intersection.c				\
			objects/triangle_intersection.c			\
			objects/materials_01.c					\
			objects/transform_initialization.c		\
			objects/transform_angle_calculation.c	\
			lighting/lighting_01.c					\
			threading/threading_01.c				\
			threading/threading_02.c
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

$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(COMPILE_FLAGS) $^ $(MLX_FLAGS) -o $@

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
# ---------------------------------------------------------------------------- #
neat: all clean
	clear
# ---------------------------------------------------------------------------- #
optimized: COMPILE_FLAGS += $(OPTIMIZATION_FLAGS)
optimized: re
# ---------------------------------------------------------------------------- #
debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re
# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re neat debug
# ---------------------------------------------------------------------------- #
