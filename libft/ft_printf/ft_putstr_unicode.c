/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:18:17 by aantropo          #+#    #+#             */
/*   Updated: 2018/12/03 19:21:38 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_unicode	ft_init_struct(unsigned char c1, unsigned char c2,
		unsigned char c3, unsigned char c4)
{
	t_unicode	symb;

	symb.b1 = c1;
	symb.b2 = c2;
	symb.b3 = c3;
	symb.b4 = c4;
	return (symb);
}

static int	write_two_bytes(t_unicode unicode_c)
{
	write(1, &unicode_c.b1, 1);
	write(1, &unicode_c.b2, 1);
	return (1);
}

static int	write_three_bytes(t_unicode unicode_c)
{
	write(1, &unicode_c.b1, 1);
	write(1, &unicode_c.b2, 1);
	write(1, &unicode_c.b3, 1);
	return (2);
}

static int	write_four_bytes(t_unicode unicode_c)
{
	write(1, &unicode_c.b1, 1);
	write(1, &unicode_c.b2, 1);
	write(1, &unicode_c.b3, 1);
	write(1, &unicode_c.b4, 1);
	return (3);
}

int			ft_putstr_unicode(char *str)
{
	int			i;
	t_unicode	unicode_c;

	i = 0;
	while (str[i])
	{
		unicode_c = ft_init_struct(str[i], str[i + 1], str[i + 2], str[i + 3]);
		if ((unicode_c.b1 >> 5) == 0x6 && (unicode_c.b2 >> 6) == 0x2)
			i += write_two_bytes(unicode_c);
		else if ((unicode_c.b1 >> 4) == 0xE && (unicode_c.b2 >> 6) == 0x2
			&& (unicode_c.b3 >> 6) == 0x2)
			i += write_three_bytes(unicode_c);
		else if ((unicode_c.b1 >> 3) == 0x1E && (unicode_c.b2 >> 6) == 0x2 &&
			(unicode_c.b3 >> 6) == 0x2 && (unicode_c.b4 >> 6) == 0x2)
			i += write_four_bytes(unicode_c);
		else if (str[i] < 127 || MB_CUR_MAX == 1)
			write(1, &str[i], 1);
		i++;
	}
	return (i);
}
