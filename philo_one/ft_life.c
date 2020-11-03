/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:33:41 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/03 10:54:59 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		ft_counter(t_state *state)
{
	int		amount;
	int		i;

	i = -1;
	amount = 0;
	while (amount < state->must_eat_count)
	{
		printf("\n-----------------%i-----------------------------------------------------------\n", state->amount);
		while (++i < state->amount)
		{
			pthread_mutex_lock(&state->philo[i].eat_m);
		}
		amount++;
	}
	printf("\nHOLAAAAAAAAAAAAAAAAAAAAA\n");
	message(&state->philo[0], OVER);
	pthread_mutex_unlock(&state->somebody_dead_m);
	return (0);
}

void		ft_eat_counter(t_state *state)
{
	pthread_t id;

	if (state->must_eat_count > 0)
	{
		if (pthread_create(&id, NULL, (void *)&ft_counter, state) != 0)
			return ;
	}
}

void		ft_monitor(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			message(philo, DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->somebody_dead_m);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}
