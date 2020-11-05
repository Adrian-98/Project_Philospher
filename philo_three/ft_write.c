/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:51:04 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/05 21:07:33 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static char	*get_message(int type)
{
	if (type == EAT)
		return (" is EATING\n");
	else if (type == SLEEP)
		return (" is SLEEPING\n");
	else if (type == FORK)
		return (" has taken the FORKS\n");
	else if (type == THINK)
		return (" is THINKING\n");
	else if (type == OVER)
		return ("PHILOSOPHERS HAVE SURVIVED!!\n");
	return (" IS DEAD\n");
}

void		message(t_philo *philo, int type)
{
	int	done;

	done = 0;
	sem_wait(philo->state->write_m);
	sem_wait(philo->state->dead_write_m);
	ft_putnbr_fd(get_time() - philo->state->start, 1);
	write(1, "\t", 1);
	if (type != OVER)
		ft_putnbr_fd(philo->position + 1, 1);
	write(1, get_message(type), ft_strlen(get_message(type)));
	if (type < DIED)
		sem_post(philo->state->dead_write_m);
	sem_post(philo->state->write_m);
}
