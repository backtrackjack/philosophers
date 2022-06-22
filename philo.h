/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:30:57 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/22 14:21:59 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_vars
{
	long int	start_time;
	int			num_philos;
	int			*fork_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;

}	t_vars;

typedef struct s_philo
{
	t_vars			v;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		philo;
	int				num;
	int				*times_eaten;
}	t_philo;

#endif
