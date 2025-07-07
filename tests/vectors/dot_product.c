/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:55:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/07 10:38:47 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_vec4	v1;
	t_vec4	v2;

	printf("\n");
	v1 = (t_vec4){0};
	v2 = (t_vec4){
		._[0] = 1,
		._[1] = 1,
		._[2] = 1
	};
	print_vec(&v1);
	print_vec(&v2);
	printf("dot product:	%f\n\n", dot_product(&v1, &v2));
	v1 = (t_vec4){
		._[0] = 1,
		._[1] = 2,
		._[2] = 3
	};
	v2 = (t_vec4){
		._[0] = 4,
		._[1] = 5,
		._[2] = 6
	};
	print_vec(&v1);
	print_vec(&v2);
	printf("dot product:	%f\n\n", dot_product(&v1, &v2));
	v1 = (t_vec4){
		._[0] = 1,
		._[1] = 0,
		._[2] = 0
	};
	v2 = (t_vec4){
		._[0] = 0,
		._[1] = 1,
		._[2] = 0
	};
	print_vec(&v1);
	print_vec(&v2);
	printf("dot product:	%f\n\n", dot_product(&v1, &v2));
	return (0);
}
