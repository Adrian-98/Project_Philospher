/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:26:47 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/02 20:42:58 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void		init_philos(t_state *state)
{
	int i;

	if (!(state->philo =(t_philo*)malloc(sizeof(*(state->philo)) * state->amount)))
        return ;
	if (!(state->forks_m = (pthread_mutex_t*)
		malloc(sizeof(*(state->forks_m)) * state->amount)))
	i = 0;
	pthread_mutex_init(&state->write_m, NULL);
	while (i < state->amount)
	{
		state->philo[i].position = i;
		state->philo[i].is_eating = 0;
		state->philo[i].lfork = i;
		state->philo[i].rfork = (i + 1) % state->amount;
		state->philo[i].eat_count = 0;
		state->philo[i].state = state;
		state->philo[i].forks_m = state->forks_m;
		pthread_mutex_init(&state->philo[i].mutex, NULL);
		pthread_mutex_init(&state->philo[i].eat_m, NULL);
		pthread_mutex_lock(&state->philo[i].eat_m);
		i++;
	}
}

int			fill_struct(t_state *state, int argc, char **argv)
{
	t_philo *philo;
	
	pthread_mutex_init(&state->somebody_dead_m, NULL);
	pthread_mutex_lock(&state->somebody_dead_m);
	state->amount = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat_count = ft_atoi(argv[5]);
	else
		state->must_eat_count = 0;
	if (state->amount < 2 || state->amount > 200 || state->time_to_die < 60
		|| state->time_to_eat < 60 || state->time_to_sleep < 60
		|| state->must_eat_count < 0)
		return (0);
	state->forks_m = NULL;
	state->philo = NULL;
	return (1);
}

int		start_threads(t_state *state)
{
	pthread_t	id[state->amount];
	int i;

	state->start = get_time();
	init_philos(state);
	i = 0;
	while (i < state->amount)
		pthread_mutex_init(&state->forks_m[i++], NULL);
		
	if (state->must_eat_count > 0)
	{
		ft_eat_counter(state);	
	}
	i = -1;
	while (++i < state->amount)
	{
		state->philo[i].last_eat = get_time();
		if(pthread_create(&id[i], NULL, (void *)&ft_body, &state->philo[i]) != 0)
			return (ft_error("Error: creating threads\n"));
		usleep(100);
	}
	i = 0;
	return 0;
}

int			main(int argc, char **argv)
{
	t_state	*state;

	if (!(state = malloc(sizeof(t_state))))
		return(ft_error("Error: malloc failed\n"));
	if (argc < 5 || argc > 6)
		return(ft_error("ERROR :wrong number of arguments \n"));
	if (fill_struct(state, argc, argv) == 0)
			return(ft_error("Error : wrong parameters or malloc fail\n"));
	start_threads(state);
	pthread_mutex_lock(&state->somebody_dead_m);
	return (0);
}