/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_body.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:41:17 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/10/29 17:24:15 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void		ft_eat(t_philo *philo)
{
	printf("------------%i\n", philo->lfork);
	pthread_mutex_lock(&philo->state->forks_m[philo->lfork]);
	printf("----------------1\n");
	printf("filosofo nº%d coge tenedor\n", philo->lfork);
	pthread_mutex_lock(&philo->state->forks_m[philo->rfork]);
	printf("filosofo nº%d coge tenedor\n", philo->lfork);
	printf("filosofo nº%d esta comiendo\n", philo->lfork);
	usleep(philo->is_eating * 1000);
	pthread_mutex_unlock(&philo->state->forks_m[philo->lfork]);
	pthread_mutex_unlock(&philo->state->forks_m[philo->rfork]);
}

void	ft_sleep(t_philo *philo)
{
	write(1, "filosofo esta durmiendo nº", 28);
	write(1, &philo->lfork, 1);
	write(1, "\n", 1);
	usleep(philo->state->time_to_sleep * 1000);
}

void		ft_body(t_philo *philo)
{
	printf("HOLAA2\n");
	while (1)
	{
		printf("HOLAA3\n");
		ft_eat(philo);
		ft_sleep(philo);
	}
}
