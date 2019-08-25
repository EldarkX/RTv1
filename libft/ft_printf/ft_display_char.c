/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:51:37 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/30 13:51:39 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_check_size_of_symbol(unsigned int nbr)
{
	if (nbr <= 127 || (MB_CUR_MAX == 1 && nbr <= 255))
		return (1);
	else if (nbr <= 2047 && nbr > 127)
		return (2);
	else if (nbr <= 65535 && nbr > 2047)
		return (3);
	return (4);
}

int		ft_manage_char(va_list args, t_format *f)
{
	int				space_cnt;
	int				cnt;
	unsigned int	nbr;

	cnt = 0;
	if (f->type == 'c' && f->mod == 2)
		nbr = (wchar_t)va_arg(args, unsigned int);
	else if (f->type == 'C')
		nbr = (wint_t)va_arg(args, unsigned int);
	else
		nbr = (unsigned char)va_arg(args, int);
	space_cnt = f->width - (ft_check_size_of_symbol(nbr));
	if (ft_strchr(f->flags, '-'))
	{
		ft_putchar_unicode(nbr);
		while (space_cnt-- > 0 && ++cnt)
			ft_putchar(' ');
	}
	else
	{
		while (space_cnt-- > 0 && ++cnt)
			ft_putchar(ft_strchr(f->flags, '0') ? '0' : ' ');
		ft_putchar_unicode(nbr);
	}
	return (cnt + (ft_check_size_of_symbol(nbr)));
}
