/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:47:31 by dcompreh          #+#    #+#             */
/*   Updated: 2022/06/15 17:11:22 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_for_one(t_philos *philo)
{
	if (proverka(philo))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	take_forks(philo);
	f_sleep(philo, 3);
	if (proverka(philo))
		return (1);
	return (0);
}

int	i_ate(t_philos *philo)
{
	pthread_mutex_lock(philo->sms);
	need_to_print(philo, 1);
	pthread_mutex_unlock(philo->sms);
	pthread_mutex_lock(philo->ex);
	philo->time = time_in();
	pthread_mutex_unlock(philo->ex);
	f_sleep(philo, 1);
	return (0);
}
