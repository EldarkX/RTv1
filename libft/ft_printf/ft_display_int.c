/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:52:05 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/28 12:52:06 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_transform_int(va_list args, t_format *f)
{
	intmax_t	nbr;

	if (f->mod == 0 && f->type != 'D')
		nbr = (char)va_arg(args, int);
	else if (f->mod == 1 && f->type != 'D')
		nbr = (short)va_arg(args, int);
	else if (f->mod == 2 || f->type == 'D')
		nbr = va_arg(args, long);
	else if (f->mod == 3)
		nbr = va_arg(args, long long);
	else if (f->mod == 4)
		nbr = va_arg(args, intmax_t);
	else if (f->mod == 5)
		nbr = (size_t)va_arg(args, long);
	else
		nbr = va_arg(args, int);
	if (f->type == 'D')
		f->type = ft_tolower(f->type);
	return (ft_itoa_base(nbr, 10));
}

char	*ft_transform_u_int(va_list args, t_format *f)
{
	intmax_t	nbr;

	if (f->mod == 0 && f->type != 'U' && f->type != 'O' && f->type != 'p')
		nbr = (unsigned char)va_arg(args, unsigned int);
	else if (f->mod == 1 && f->type != 'U' && f->type != 'O' && f->type != 'p')
		nbr = (unsigned short)va_arg(args, unsigned int);
	else if (f->mod == 2 || f->type == 'U' || f->type == 'O')
		nbr = va_arg(args, unsigned long);
	else if (f->mod == 3 || f->type == 'p')
		nbr = va_arg(args, unsigned long long);
	else if (f->mod == 4)
		nbr = va_arg(args, uintmax_t);
	else if (f->mod == 5)
		nbr = (size_t)va_arg(args, unsigned long);
	else
		nbr = va_arg(args, unsigned int);
	f->type = (f->type == 'U' || f->type == 'O' ?
			ft_tolower(f->type) : f->type);
	if (f->type == 'o')
		return (ft_u_itoa_base(nbr, 8));
	if (f->type == 'X')
		return (ft_u_itoa_base(nbr, 16));
	if (f->type == 'x' || f->type == 'p')
		return (ft_str_to_lower(ft_u_itoa_base(nbr, 16)));
	return (ft_u_itoa_base(nbr, 10));
}

void	ft_manage_int_3(t_format *f, int *cnt, int len, int cnt_spec)
{
	ft_putstr(f->prefix);
	cnt_spec = (f->precision > len ? f->precision - len : 0);
	cnt_spec = (ft_strlen(f->prefix) == 1 && f->prefix[0] == '0' ?
			cnt_spec - 1 : cnt_spec);
	while (cnt_spec-- > 0 && ++(*cnt))
		ft_putchar('0');
	cnt_spec = f->width - *cnt - len;
	ft_putstr(f->string);
	while (cnt_spec-- > 0 && ++(*cnt))
		ft_putchar(' ');
}

void	ft_manage_int_2(t_format *f, int *cnt, int len, int cnt_spec)
{
	if (ft_strchr(f->flags, '0') && f->precision == -1)
	{
		ft_putstr(f->prefix);
		cnt_spec = f->width - *cnt - len;
		while (cnt_spec-- > 0 && ++(*cnt))
			ft_putchar('0');
		ft_putstr(f->string);
	}
	else
	{
		cnt_spec = f->precision > len ? f->precision - len : 0;
		cnt_spec = ft_strchr(f->flags, '#') && f->type == 'o' &&
				f->precision > len ? cnt_spec - 1 : cnt_spec;
		f->width = f->width - cnt_spec - *cnt - len;
		while (f->width-- > 0 && ++(*cnt))
			ft_putchar(' ');
		ft_putstr(f->prefix);
		cnt_spec = (f->precision > len ? f->precision - len : 0);
		cnt_spec = ft_strlen(f->prefix) == 1 && f->prefix[0] == '0' ?
				cnt_spec - 1 : cnt_spec;
		while (cnt_spec-- > 0 && ++(*cnt))
			ft_putchar('0');
		ft_putstr(f->string);
	}
}

int		ft_manage_int(t_format *f, int len)
{
	int	cnt_spec;
	int	cnt;

	cnt_spec = 0;
	f->prefix = ft_add_prefix(f);
	len = ft_strlen(f->string);
	cnt = ft_strlen(f->prefix);
	if (f->precision == 0 && !ft_strcmp(f->string, "0"))
	{
		if (f->type == 'd' || f->type == 'i')
			ft_putstr(ft_add_prefix(f));
		if (ft_strchr(f->flags, '#') && f->type == 'o')
			ft_putchar('0');
		else
			len = 0;
		cnt -= (f->type != 'd' && f->type != 'i' ? ft_strlen(f->prefix) : 0);
		while (f->width-- > 0 && ++cnt)
			ft_putchar(' ');
	}
	else if (ft_strchr(f->flags, '-'))
		ft_manage_int_3(f, &cnt, len, cnt_spec);
	else
		ft_manage_int_2(f, &cnt, len, cnt_spec);
	ft_strdel(&f->prefix);
	return (cnt + len);
}
