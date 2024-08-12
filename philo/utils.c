/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:43:18 by dcompreh          #+#    #+#             */
/*   Updated: 2022/06/15 19:00:01 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_take_fork(t_philos *philo)
{
	if (proverka(philo))
		return ;
	printf("%lld %d has taken a fork\n", time_in() - philo->start,
		philo->id);
	if (proverka(philo))
		return ;
}

void	take_forks(t_philos *philo)
{
	pthread_mutex_lock(philo->sms);
	print_take_fork(philo);
	pthread_mutex_unlock(philo->sms);
}

void	lock_forks(t_philos *philo)
{
	if (proverka(philo))
		return ;
	if ((philo->id % 2) != 0)
	{
		if (proverka(philo))
			return ;
		pthread_mutex_lock(philo->left_fork);
		take_forks(philo);
		if (proverka(philo))
			return ;
		pthread_mutex_lock(philo->right_fork);
		take_forks(philo);
	}
	else
	{
		if (proverka(philo))
			return ;
		pthread_mutex_lock(philo->right_fork);
		take_forks(philo);
		if (proverka(philo))
			return ;
		pthread_mutex_lock(philo->left_fork);
		take_forks(philo);
	}
}

void	unlock_forks(t_philos *philo)
{
	if ((philo->id % 2) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	f_sleep(t_philos *philo, int i)
{
	long long	t;

	t = time_in();
	while (i == 1 && (time_in() - t) < philo->time_eat)
		usleep(100);
	while (i == 2 && (time_in() - t) < philo->time_sleep)
		usleep(100);
	while (i == 3 && (time_in() - t) < philo->time_to_die)
		usleep(100);
}
