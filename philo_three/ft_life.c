/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:33:41 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/05 20:16:36 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		ft_counter(t_state *state)
{
	int i;
	int j;

	i = -1;
	while (++i < state->amount)
	{
		j = -1;
		while (++j < state->must_eat_count)
			sem_wait(state->philo[j].eat_count_m);
	}
	message(&state->philo[0], OVER);
	sem_post(state->somebody_dead_m);
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

void			ft_monitor(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			message(philo, DIED);
			sem_post(philo->mutex);
			sem_post(philo->state->somebody_dead_m);
			return ;
		}
		sem_post(philo->mutex);
		usleep(1000);
	}
}
