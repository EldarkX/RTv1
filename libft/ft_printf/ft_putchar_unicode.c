/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_unicode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:36:53 by aantropo          #+#    #+#             */
/*   Updated: 2018/12/08 12:00:17 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_four_bytes(unsigned int nbr)
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;

	a = 0xF0;
	b = 0x80;
	c = 0x80;
	d = 0x80;
	a = a | ((nbr & 0x1C0000) >> 18);
	b = b | ((nbr & 0x3F000) >> 12);
	c = c | ((nbr & 0xFC0) >> 6);
	d = d | (nbr & 0x3F);
	write(1, &a, 1);
	write(1, &b, 1);
	write(1, &c, 1);
	write(1, &d, 1);
}

void	ft_three_bytes(unsigned int nbr)
{
	unsigned int a;
	unsigned int b;
	unsigned int c;

	a = 0xE0;
	b = 0x80;
	c = 0x80;
	a = a | ((nbr & 0xF000) >> 12);
	b = b | ((nbr & 0xFC0) >> 6);
	c = c | (nbr & 0x003F);
	write(1, &a, 1);
	write(1, &b, 1);
	write(1, &c, 1);
}

void	ft_two_bytes(unsigned int nbr)
{
	unsigned int a;
	unsigned int b;

	a = 0xC0;
	b = 0x80;
	a = a | ((nbr & 0x07C0) >> 6);
	b = b | (nbr & 0x003F);
	write(1, &a, 1);
	write(1, &b, 1);
}

int		ft_putchar_unicode(unsigned int nbr)
{
	if (nbr <= 127 || (MB_CUR_MAX == 1 && nbr <= 255))
	{
		write(1, &nbr, 1);
		return (1);
	}
	else if (nbr <= 2047 && nbr > 127)
	{
		ft_two_bytes(nbr);
		return (2);
	}
	else if (nbr <= 65535 && nbr > 2047)
	{
		ft_three_bytes(nbr);
		return (3);
	}
	else
		ft_four_bytes(nbr);
	return (4);
}
