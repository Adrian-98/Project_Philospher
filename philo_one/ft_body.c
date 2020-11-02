/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_body.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:41:17 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/02 16:52:13 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void		ft_eat_counter(t_state *state)
{
	pthread_t id;

	if (state->must_eat_count > 0)
	{
		if (pthread_create(&id, NULL, (void *)&ft_counter, state) != 0)
			return ;
	}
}

void		ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_m[philo->lfork]);
	printf("filosofo nº%d COGE tenedor izquierdo\n", philo->lfork);
	if (pthread_mutex_lock(&philo->state->forks_m[philo->rfork]) != 0)
	{
		pthread_mutex_unlock(&philo->state->forks_m[philo->lfork]);
		usleep(100);
		return (ft_eat(philo));
	}
	printf("filosofo nº%d COGE tenedor derecho\n", philo->lfork);
	printf("filosofo nº%d esta COMIENDO\n", philo->lfork);
	pthread_mutex_unlock(&philo->eat_m);
	usleep(philo->state->time_to_eat * 1000);
}

void	ft_drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->forks_m[philo->lfork]);
	printf("filosofo nº%d SUELTA tenedor izquierdo\n", philo->lfork);
	pthread_mutex_unlock(&philo->state->forks_m[philo->rfork]);
	printf("filosofo nº%d SUELTA tenedor derecho\n", philo->lfork);
}

void	ft_sleep(t_philo *philo)
{
	printf("filosofo esta DURMIENDO nº%i\n", philo->lfork);
	usleep(philo->state->time_to_sleep * 1000);
	printf("filosofo deja de DORMIR nº%i\n", philo->lfork);
}

void		*ft_body(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		ft_eat(philo);
		ft_drop_fork(philo);
		ft_sleep(philo);
	}
}
