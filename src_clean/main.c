/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 17:59:12 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac < 5 || ac > 6)
		return (printf("wrong amount ac"));
	if (!handler_parser(ac, av))
		exit (1);
	table = init_table_philos(ac, av);
	if (!table)
		exit (1);
	if (!begin_process(table))
		exit (1);
	end_process(table);
	return (0);
}
