/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:01:45 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 13:01:47 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char		*ft_init_str(int n, char *str, unsigned int tmp, long digit)
{
	int i;

	i = 0;
	(n < 0) ? str[i++] = '-' : 0;
	while (digit > 0)
	{
		str[i++] = tmp / digit + '0';
		tmp = tmp - (tmp / digit) * digit;
		digit /= 10;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	unsigned int	tmp;
	unsigned int	tmp2;
	long			digit;
	char			*str;
	int				i;

	i = 1;
	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		i++;
	}
	digit = 1;
	tmp2 = tmp;
	while (tmp2 > 9)
	{
		tmp2 /= 10;
		digit *= 10;
		i++;
	}
	if (!(str = ft_strnew(i)))
		return (NULL);
	str = ft_init_str(n, str, tmp, digit);
	return (str);
}
