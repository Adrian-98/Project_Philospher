/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:51:04 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/04 20:30:50 by adrian           ###   ########.fr       */
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

int
	display_message(t_philo *philo, int type)
{
	static int	done = 0;
	int			ret;

	if (sem_wait(philo->state->write_m) != 0)
		return (1);
	ret = 1;
	if (!done)
	{
		ft_putnbr_fd(get_time() - philo->state->start, 1);
		write(1, "\t", 1);
		if (type != OVER)
			ft_putnbr_fd(philo->position + 1, 1);
		if (type >= DIED)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
		ret = 0;
	}
	if (sem_post(philo->state->write_m))
		return (1);
	return (ret);
}