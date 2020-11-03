/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_body.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:41:17 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/03 18:02:01 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void		ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	message(philo, EAT);
	usleep(philo->state->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	philo->state->eat_m += 1;
}

void		ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_m[philo->lfork]);
	pthread_mutex_lock(&philo->state->forks_m[philo->rfork]);
	message(philo, FORK);
}

void		ft_drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->forks_m[philo->lfork]);
	pthread_mutex_unlock(&philo->state->forks_m[philo->rfork]);
}

void		ft_sleep(t_philo *philo)
{
	message(philo, SLEEP);
	usleep(philo->state->time_to_sleep * 1000);
}

void		*ft_body(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&tid, NULL, (void *)&ft_monitor, philo_v) != 0)
		return ((void*)1);
	while (1)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_drop_fork(philo);
		ft_sleep(philo);
	}
	return ((void*)0);
}
