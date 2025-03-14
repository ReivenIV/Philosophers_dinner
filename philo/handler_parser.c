/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:10:19 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/14 09:56:56 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	handler_parser(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;												// We start i=1 to avoid the first arg (./philo)
	while (i < ac)
	{
		if (!has_only_digits(av[i]))
			return(printf("wrong inputs format\n"), false);
		nb = nbs_atoi(av[i]);
		if (i == 1 && (nb <= 0 || nb > 200))
			return(printf("wrong amount of philos my dear\n"), false);
		if ((i > 1 && i < 5) && nb < 60)
			return(printf("invalid inputs format my dear\n"), false);
		if (i == 5 && nb <= 0)
			return (printf("meals darlin ?\n"), false);	
		i++;
	}
	return (true);
}
