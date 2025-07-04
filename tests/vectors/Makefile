# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/07/04 14:50:32 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTS	:=	\
			vec_len.out			\
			new_unit_vec.out	\
			normalize_vec.out	\
			new_scaled_vec.out
#		  	scale_vec_in_place

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
