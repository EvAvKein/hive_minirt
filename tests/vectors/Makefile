# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 10:27:18 by jvarila           #+#    #+#              #
#    Updated: 2025/07/07 18:56:28 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTS	:=	\
			vec_len.out			\
			unit_vec.out		\
			normalize_vec.out	\
			scaled_vec.out		\
			scale_vec.out		\
			dot_product.out

CC				:= cc
COMPILE_FLAGS	:= -Wall -Wextra -Werror -g
# ---------------------------------------------------------------------------- #
DEBUG_FLAGS	:=	-g
# ---------------------------------------------------------------------------- #
LIBFT_DIR	:=	../../libft_plus
LIBFT_LIB	:=	$(LIBFT_DIR)/libft_plus.a
# ---------------------------------------------------------------------------- #
MLX_REPO		:= https://github.com/codam-coding-college/MLX42.git
MLX_DIR			:= ../../MLX42
MLX_BUILD_DIR	:= $(MLX_DIR)/build
MLX_LIB			:= $(MLX_BUILD_DIR)/libmlx42.a
# ---------------------------------------------------------------------------- #
SRC_DIR	:=	../../src
SRC		:=	\
			vectors/vectors_01.c	\
			vectors/vectors_02.c
# ---------------------------------------------------------------------------- #
INC_DIR			:=	../../inc
INC_FILES		:=	minirt.h settings.h
HEADERS			:=	$(INC_FILES:%=$(INC_DIR)/%)
COMPILE_FLAGS	+=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include \
					-I$(MLX_DIR)/include/MLX42
# ---------------------------------------------------------------------------- #
OBJ_DIR		:=	obj
OBJ			:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
.SECONDARY	:=	$(OBJ)
# ---------------------------------------------------------------------------- #
.DEFAULT = all

all: $(TESTS)

$(TESTS): %.out: %.c $(OBJ)
	$(CC) $(COMPILE_FLAGS) $(OBJ) $(LIBFT_LIB) $< -o $@ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(COMPILE_FLAGS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR) -s --no-print-directory

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
