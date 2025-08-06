/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:09:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/03 12:20:36 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include "MLX42.h"

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

// Rotation
# ifndef KEYBIND_RX
#  define KEYBIND_RX		MLX_KEY_UP
# endif
# ifndef KEYBIND_RY
#  define KEYBIND_RY		MLX_KEY_RIGHT
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

// Move faster
# ifndef KEYBIND_FAST
#  define KEYBIND_FAST		MLX_KEY_LEFT_SHIFT
# endif
# ifndef MOVEMENT_BASE
#  define MOVEMENT_BASE		1
# endif
# ifndef MOVEMENT_MULT
#  define MOVEMENT_MULT		20
# endif

# ifndef ROTATION_BASE
#  define ROTATION_BASE		1 * RADIANS_PER_DEGREE
# endif
# ifndef ROTATION_MULT
#  define ROTATION_MULT		3
# endif

// Screenshot
# ifndef KEYBIND_SAVE
#  define KEYBIND_SAVE		MLX_KEY_SPACE
# endif

// Movement
# ifndef KEYBIND_QUIT
#  define KEYBIND_QUIT		MLX_KEY_ESCAPE
# endif

// Resolution
# ifndef RES_X
#  define RES_X		1920	// 3840	1920	1280
# endif
# ifndef RES_Y
#  define RES_Y		1080	// 2160	1080	720
# endif

# ifndef THREADS
#  define THREADS	8
# endif

# ifndef TICK
#  define TICK		500
# endif

# ifndef EPSILON
#  define EPSILON	0.0001
# endif

#endif
