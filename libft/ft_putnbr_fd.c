/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:24:55 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 17:24:57 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	tmp;
	unsigned int	tmp2;
	long			digit;

	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		ft_putchar_fd('-', fd);
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
		ft_putchar_fd(tmp / digit + '0', fd);
		tmp = tmp - (tmp / digit) * digit;
		digit /= 10;
	}
}
