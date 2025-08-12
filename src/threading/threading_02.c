/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:06:23 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 15:06:32 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*monitor_thread(void *arg)
{
	size_t	i;

	(void)arg;
	pthread_mutex_lock(&dat()->lock);
	pthread_mutex_unlock(&dat()->lock);
	while (!dat()->stop_threads)
	{
		if (dat()->threads_waiting == dat()->active_threads)
		{
			i = -1;
			while (++i < THREADS)
				dat()->thread_can_proceed[i] = true;
		}
		else
			usleep(TICK * 100);
	}
	return (NULL);
}
