/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:55:16 by rita          #+#    #+#             */
/*   Updated: 2022/07/08 12:57:03 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* has_only_digits:
*	Checks if a string contains only digits 0 - 9.
*	Returns true if the string only contains digits.
*	Returns false if the string contains a character that is not a digit.
*/
static bool	has_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

/* nbs_atoi:
*	Converts a digit-only string into a positive integer.
*	Returns the converted number between 0 and INT MAX.
*	Returns -1 if the converted number exceeds INT MAX.
*/
int	nbs_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/* are_valid_input:
*	Checks if all required arguments are valid, i.e. is a string of
*	digits only, which does not exceed INT MAX. Also checks if the number
*	of philosophers is valid (between 1 and MAX_PHILOS).
*	Returns true if all arguments are valid, false if one of them is invalid.
*/
// bool	are_valid_input(int ac, char **av)
// {
// 	int	i;
// 	int	nb;

// 	i = 1;
// 	while (i < ac)
// 	{
// 		if (!has_only_digits(av[i]))
// 			return (msg(STR_ERR_INPUT_DIGIT, av[i], false));
// 		nb = nbs_atoi(av[i]);
// 		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
// 			return (msg(STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS, false));
// 		if (i != 1 && nb == -1)
// 			return (msg(STR_ERR_INPUT_DIGIT, av[i], false));
// 		i++;
// 	}
// 	return (true);
// }

bool	are_valid_input(int ac, char **av)
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