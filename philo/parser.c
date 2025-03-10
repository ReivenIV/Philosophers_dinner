/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:10:19 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/10 17:43:38 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Will check if the string is only made out of (char)numbers 
static bool has_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}


bool	are_inputs_valid(int ac, char **av)
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
		if (i > 1 && nb < 60)
			return(printf("invalid inputs format my dear\n"), false);
		i++;
	}
	return (true);
}
