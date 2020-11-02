/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:33:41 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/02 19:19:27 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		ft_counter(t_state *state)
{
	int		amount;
	int		i;

	i = 0;
	amount = 0;
	while (amount < state->must_eat_count)
	{
		while (i < state->amount)
			pthread_mutex_lock(&state->philo[i++].eat_m);
		amount++;
	}
	ft_error("HAN COMIDO");
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
			printf("filosofo %i ha muerto\n", philo->position);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->somebody_dead_m);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}
