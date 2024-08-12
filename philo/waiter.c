/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:53:10 by dcompreh          #+#    #+#             */
/*   Updated: 2022/06/15 16:44:22 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_arg *arg, int *j)
{
	int	i;

	i = *j;
	while (i < arg->n_philo)
	{
		pthread_mutex_lock(&arg->exx);
		if ((time_in() - arg->philo[i].time) > arg->time_to_die)
		{
			arg->philo[i].s_dead = 1;
			printf ("%lld %d died\033[0m\n",
				time_in() - arg->philo[i].start, arg->philo[i].id);
			pthread_mutex_unlock(&arg->exx);
			break ;
		}
		pthread_mutex_unlock(&arg->exx);
		i++;
	}
	return (i);
}

int	check_death(t_arg *arg)
{
	int	i;
	int	s;

	i = 0;
	i = death(arg, &i);
	pthread_mutex_lock(&arg->exx);
	if (arg->philo[i].s_dead == 1)
	{
		s = i;
		i = 0;
		pthread_mutex_unlock(&arg->exx);
		while (i < arg->n_philo)
		{
			if (i == s)
				i++;
			pthread_mutex_lock(&arg->exx);
			arg->philo[i].s_exit = 1;
			pthread_mutex_unlock(&arg->exx);
			i++;
		}
		return (1);
	}
	pthread_mutex_unlock(&arg->exx);
	return (0);
}

int	s_exit(t_arg *arg, int ate)
{
	int	i;

	if (ate == arg->n_philo)
	{
		i = -1;
		pthread_mutex_lock(&arg->exx);
		while (++i < arg->n_philo)
			arg->philo[i].s_exit = 1;
		pthread_mutex_unlock(&arg->exx);
		return (1);
	}
	return (0);
}

void	waiter_chec(t_arg *arg)
{
	int	i;
	int	ate;

	while (1)
	{
		i = 0;
		ate = 0;
		pthread_mutex_lock(&arg->exx);
		while (i < arg->n_philo)
		{
			if (arg->philo[i].must_eat <= 0)
				ate++;
			i++;
		}
		pthread_mutex_unlock(&arg->exx);
		if (s_exit(arg, ate))
			break ;
		if (check_death(arg))
			break ;
	}
}
