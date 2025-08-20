/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:09:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/15 13:58:28 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

/* ---------------------------------------------------------------- PRECISION */

# ifndef EPSILON
#  define EPSILON	0.0001
# endif

# ifndef MAX_DIST
#  define MAX_DIST	1000000
# endif

# ifndef STARTING_PRECISION
#  define STARTING_PRECISION	64
# endif

/* ------------------------------------------------ INITIAL WINDOW RESOLUTION */

# ifndef RES_X
#  define RES_X		1920	// 3840	1920	1280
# endif

# ifndef RES_Y
#  define RES_Y		1080	// 2160	1080	720
# endif

/* ------------------------------------------------------------------ THREADS */

# ifndef THREADS
#  define THREADS	5
# endif

# ifndef TICK
#  define TICK		50
# endif

/* ----------------------------------------------------------------------- UI */

// Movement
# ifndef KEYBIND_MLEFT
#  define KEYBIND_MLEFT		MLX_KEY_A
# endif

# ifndef KEYBIND_MRIGHT
#  define KEYBIND_MRIGHT	MLX_KEY_D
# endif

# ifndef KEYBIND_MFORWARD
#  define KEYBIND_MFORWARD	MLX_KEY_W
# endif

# ifndef KEYBIND_MBACKWARD
#  define KEYBIND_MBACKWARD	MLX_KEY_S
# endif

# ifndef KEYBIND_MUP
#  define KEYBIND_MUP		MLX_KEY_E
# endif

# ifndef KEYBIND_MDOWN
#  define KEYBIND_MDOWN		MLX_KEY_Q
# endif

# ifndef MOVEMENT_BASE
#  define MOVEMENT_BASE		1
# endif

# ifndef MOVEMENT_MULT
#  define MOVEMENT_MULT		20
# endif

// Rotation
# ifndef KEYBIND_RX
#  define KEYBIND_RX		MLX_KEY_UP
# endif

# ifndef KEYBIND_RY
#  define KEYBIND_RY		MLX_KEY_RIGHT
# endif

# ifndef ROTATION_BASE
#  define ROTATION_BASE		RADIANS_PER_DEGREE
# endif

# ifndef ROTATION_MULT
#  define ROTATION_MULT		3
# endif

// Speed modifier
# ifndef KEYBIND_FAST
#  define KEYBIND_FAST		MLX_KEY_LEFT_SHIFT
# endif

// Reverse rotation
# ifndef KEYBIND_RRX
#  define KEYBIND_RRX		MLX_KEY_DOWN
# endif

# ifndef KEYBIND_RRY
#  define KEYBIND_RRY		MLX_KEY_LEFT
# endif

// Control object
# ifndef KEYBIND_OBJ
#  define KEYBIND_OBJ		MLX_KEY_LEFT_CONTROL
# endif

// FOV changing
# ifndef KEYBIND_FOV_INC
#  define KEYBIND_FOV_INC	MLX_KEY_F
# endif

# ifndef KEYBIND_FOV_DEC
#  define KEYBIND_FOV_DEC	MLX_KEY_R
# endif

# ifndef FOV_DELTA
#  define FOV_DELTA			1
# endif

// Object scaling
# ifndef KEYBIND_SCALE_INC
#  define KEYBIND_SCALE_INC	MLX_KEY_R
# endif

# ifndef KEYBIND_SCALE_DEC
#  define KEYBIND_SCALE_DEC	MLX_KEY_F
# endif

# ifndef SCALE_DELTA
#  define SCALE_DELTA		1.015
# endif

# ifndef SCALE_MULT
#  define SCALE_MULT		1.1
# endif

// Window closing
# ifndef KEYBIND_QUIT
#  define KEYBIND_QUIT		MLX_KEY_ESCAPE
# endif

// Toggle cylinder and cone caps
# ifndef KEYBIND_NO_CAP
#  define KEYBIND_NO_CAP	MLX_KEY_O
# endif

// Screenshot
# ifndef KEYBIND_SAVE
#  define KEYBIND_SAVE		MLX_KEY_SPACE
# endif

// Reset
# ifndef KEYBIND_RESET
#  define KEYBIND_RESET		MLX_KEY_P
# endif

#endif
