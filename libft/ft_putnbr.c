/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:13:09 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 17:13:11 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr(int n)
{
	unsigned int	tmp;
	unsigned int	tmp2;
	long			digit;

	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		ft_putchar('-');
	}
	digit = 1;
	tmp2 = tmp;
	while (tmp2 > 9)
	{
		tmp2 /= 10;
		digit *= 10;
	}
	while (digit > 0)
	{
		ft_putchar(tmp / digit + '0');
		tmp = tmp - (tmp / digit) * digit;
		digit /= 10;
	}
}
