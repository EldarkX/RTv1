/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:44:28 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/26 12:44:29 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_is_mode_width(char t)
{
	if (t == 'l' || t == 'h' || t == 'z' || t == 'y' || t == 'j' || t == 'L')
		return (1);
	return (0);
}

int			ft_digit_cnt_base(uintmax_t nbr, int base)
{
	int	digits;

	digits = 0;
	while (nbr)
	{
		nbr /= base;
		digits++;
	}
	return (digits == 0) ? 1 : digits;
}

uintmax_t	ft_pow(uintmax_t nbr, int pow)
{
	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	return (nbr * ft_pow(nbr, pow - 1));
}

char		*ft_itoa_base(intmax_t nbr, int base)
{
	uintmax_t			tmp;
	char				*str;
	intmax_t			size;
	intmax_t			pow;
	int					i;

	i = -1;
	size = (nbr < 0) ? 1 : 0;
	tmp = (nbr < 0) ? -nbr : nbr;
	size += ft_digit_cnt_base(tmp, base);
	pow = (nbr < 0) ? ft_pow(base, size - 3) : ft_pow(base, size - 2);
	str = ft_strnew(size);
	if (nbr < 0)
		str[++i] = '-';
	while (++i + 1 && pow > 0)
	{
		size = tmp / pow / base;
		str[i] = (size <= base && size > 9) ? size - 10 + 'A' : size + '0';
		tmp -= size * pow * base;
		pow /= base;
	}
	str[i] = (tmp > 9) ? tmp - 10 + 'A' : tmp + '0';
	return (str);
}

char		*ft_u_itoa_base(uintmax_t nbr, int base)
{
	char				*str;
	uintmax_t			size;
	uintmax_t			pow;
	int					i;

	i = 0;
	size = ft_digit_cnt_base(nbr, base);
	pow = ft_pow(base, size - 2);
	str = ft_strnew(size);
	while (pow > 0)
	{
		size = nbr / pow / base;
		str[i++] = (size <= (uintmax_t)base && size > 9) ?
				size - 10 + 'A' : size + '0';
		nbr -= size * pow * base;
		pow /= base;
	}
	str[i] = (nbr > 9) ? nbr - 10 + 'A' : nbr + '0';
	return (str);
}
