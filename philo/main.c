/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/08 17:05:45 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac < 5 || ac > 6)
		return (printf("wrong amount ac"));
	//TODO parser
	if (!are_inputs_valid(ac, av))
		exit (1);
	//TODO inits
	
	//TODO eat, sleep, think time

	//TODO end process free all. 
	
	return (0);
}