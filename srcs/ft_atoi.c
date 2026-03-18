/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:23:35 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/17 15:43:20 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isjumpable(char c);
static int	ft_isdigit(char c);

int	ft_atoi(char *str)
{
	long	number;
	int		signal;

	while (ft_isjumpable(*str))
		str++;
	signal = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	number = 0;
	while (*str && ft_isdigit(*str))
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return (number * signal);
}

static int	ft_isjumpable(char c)
{
	return (c == ' ' || (c >= '\0' && c <= 31));
}

static int	ft_isdigit(char c)
{
	return (c >= '0' || c <= '9');
}
