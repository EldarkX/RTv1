/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:41:01 by aantropo          #+#    #+#             */
/*   Updated: 2018/12/11 11:42:00 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_manage_pointer_else(t_format *f, int *cnt, int len)
{
	if (ft_strchr(f->flags, '0') && f->precision == -1)
	{
		ft_putstr(f->prefix);
		f->width = f->width - (*cnt + (f->precision > len ?
				f->precision : len));
		while (f->width-- > 0 && ++(*cnt))
			ft_putchar('0');
	}
	else
	{
		f->width = f->width - (*cnt + (f->precision > len ?
				f->precision : len));
		while (f->width-- > 0 && ++(*cnt))
			ft_putchar(' ');
		ft_putstr(f->prefix);
		f->precision = f->precision - len;
		while (f->precision-- > 0 && ++(*cnt))
			ft_putchar('0');
	}
	ft_putstr(f->string);
}

int		ft_manage_pointer(t_format *f, int len)
{
	int cnt;

	f->prefix = ft_strdup("0x");
	cnt = ft_strlen(f->prefix);
	if (f->precision == 0 && !ft_strcmp(f->string, "0"))
	{
		ft_putstr(f->prefix);
		cnt--;
	}
	else if (ft_strchr(f->flags, '-'))
	{
		ft_putstr(f->prefix);
		f->precision = f->precision - len;
		while (f->precision-- > 0 && ++cnt)
			ft_putchar('0');
		ft_putstr(f->string);
		f->width = f->width - cnt - len;
		while (f->width-- > 0 && ++cnt)
			ft_putchar(' ');
	}
	else
		ft_manage_pointer_else(f, &cnt, len);
	ft_strdel(&f->prefix);
	return (cnt + len);
}
