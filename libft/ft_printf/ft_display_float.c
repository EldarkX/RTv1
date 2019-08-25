/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 12:01:16 by aantropo          #+#    #+#             */
/*   Updated: 2018/12/08 12:01:21 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_print_f(t_format *f, uintmax_t ip, long double fp)
{
	int	cnt;
	int	first;

	cnt = 0;
	ip = (uintmax_t)fp;
	first = (ip == 0 && fp > 0) ? 1 : 0;
	fp -= ip;
	ft_putstr(ft_u_itoa_base(ip, 10));
	ft_putchar('.');
	cnt++;
	while ((ip > 0 && f->precision) || first)
	{
		fp *= 10;
		ip = (uintmax_t)fp;
		ft_putchar('0' + ip);
		fp -= ip;
		first = 0;
		f->precision--;
		cnt++;
	}
	while (f->precision-- > 0 && cnt++)
		ft_putchar('0');
	return (cnt);
}

int		ft_dislay_float(t_format *f, uintmax_t ip, long double fp)
{
	long double e;
	int			cnt;

	f->precision = (f->precision >= 0 ? f->precision : 6);
	if (f->precision == 0)
	{
		fp -= ip;
		if ((fp * 10) >= 5)
			ip += 1;
		ft_putstr(ft_u_itoa_base(ip, 10));
		if (ft_strchr(f->flags, '#'))
		{
			ft_putchar('.');
			return (1);
		}
		return (0);
	}
	e = ft_e(f->precision);
	fp = ft_find_float(f->precision, fp, e);
	cnt = ft_print_f(f, ip, fp);
	return (cnt);
}

int		ft_display_ip(t_format *f, long double nbr)
{
	int				cnt;
	uintmax_t		integer;

	cnt = (nbr < 0 || ft_strchr(f->flags, '+')
			|| ft_strchr(f->flags, ' ') ? 1 : 0);
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putstr("-");
	}
	else if (ft_strchr(f->flags, '+'))
		ft_putstr("+");
	else if (ft_strchr(f->flags, ' '))
		ft_putstr(" ");
	integer = (uintmax_t)nbr;
	cnt += ft_digit_cnt_base(integer, 10);
	cnt += ft_dislay_float(f, integer, nbr);
	return (cnt);
}

int		ft_manage_float_else(t_format *f, long double nbr)
{
	int		cnt;
	char	c;

	c = ' ';
	cnt = ft_digit_cnt_base(nbr < 0 ? -nbr : nbr, 10) + 1 + (nbr < 0 ||
			ft_strchr(f->flags, '+') || ft_strchr(f->flags, ' ') ? 1 : 0);
	f->width = f->width - ((f->precision >= 0 ? f->precision : 6) + cnt);
	if (ft_strchr(f->flags, '0'))
		c = '0';
	cnt = 0;
	while (f->width-- > 0 && ++cnt)
		ft_putchar(c);
	cnt += ft_display_ip(f, nbr);
	return (cnt);
}

int		ft_manage_float(va_list args, t_format *f)
{
	long double			nbr;
	int					cnt;

	cnt = 0;
	if (f->mod == 6)
		nbr = va_arg(args, long double);
	else
		nbr = va_arg(args, double);
	if (ft_strchr(f->flags, '-'))
	{
		cnt += ft_display_ip(f, nbr);
		while (cnt < f->width && ++cnt)
			ft_putchar(' ');
	}
	else
		cnt += ft_manage_float_else(f, nbr);
	return (cnt);
}
