/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:30:24 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 16:30:25 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static long	ft_digit(const char *str, int *i)
{
	long	digit;
	int		k;

	digit = 1;
	k = 0;
	while (ft_isdigit(str[*i]))
	{
		digit *= 10;
		*i = *i + 1;
		k++;
	}
	*i = *i - k;
	digit /= 10;
	return (digit);
}

static int	ft_num_cnt(const char *str)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (!(ft_isdigit(str[i])))
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static int	ft_space_skip(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
	|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		num_cnt;
	long	digit;
	int		sign;

	i = ft_space_skip(str);
	nbr = 0;
	sign = 0;
	num_cnt = ft_num_cnt(str);
	if (num_cnt > 18)
		return (-1);
	str[i] == '-' ? sign = 1 : 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	digit = ft_digit(str, &i);
	while (ft_isdigit(str[i]))
	{
		nbr += (str[i] - '0') * digit;
		i++;
		digit /= 10;
	}
	if (sign)
		return (nbr * -1);
	return (nbr);
}
