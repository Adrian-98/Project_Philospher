/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:27:58 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/02 16:37:36 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_state	*state;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	eat_m;
}				t_philo;
typedef struct s_state
{
	int				amount;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat_count;

	uint64_t		start;

	struct s_philo	*philo;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;

}				t_state;


int					ft_strlen(char *str);
int					ft_atoi(char const *str);
void				ft_putnbr_fd(uint64_t n, int fd);
uint64_t			get_time(void);
int					init_mutex(t_state *state);
int					start_threads(t_state *state);
void				*ft_body(void *philo_v);
void				ft_sleep(t_philo *philo);
int	 				ft_error(char *str);
void				init_philos(t_state *state);
int					fill_struct(t_state *state, int argc, char **argv);
void				ft_drop_fork(t_philo *philo);
void				ft_eat_counter(t_state *state);
int					ft_counter(t_state *state);

#endif