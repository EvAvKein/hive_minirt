/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:55:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/09 09:58:17 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_vec4	vec;

	printf("\n");
	vec = (t_vec4){};
	vec = unit_vec(&vec);
	print_vec(&vec);
	printf("len:	%f\n\n", vec_len(&vec));
	vec = (t_vec4){
		._[0] = 1,
		._[1] = 1,
		._[2] = 1
	};
	vec = unit_vec(&vec);
	print_vec(&vec);
	printf("len:	%f\n\n", vec_len(&vec));
	vec = (t_vec4){
		._[0] = 1,
		._[1] = -2,
		._[2] = 3,
		._[3] = 100
	};
	vec = unit_vec(&vec);
	print_vec(&vec);
	printf("len:	%f\n\n", vec_len(&vec));
	return (0);
}
