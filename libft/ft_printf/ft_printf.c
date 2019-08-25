/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:30:35 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/22 11:30:37 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_take_arg(va_list args, t_format *f)
{
	int cnt;

	if (f->type == 'd' || f->type == 'i' || f->type == 'D')
		f->string = ft_transform_int(args, f);
	else if (f->type == 'x' || f->type == 'X' || f->type == 'u' ||
		f->type == 'o' || f->type == 'p' || f->type == 'U' || f->type == 'O')
		f->string = ft_transform_u_int(args, f);
	if (f->type == 's' || f->type == 'S')
		cnt = ft_manage_s(args, f);
	else if (f->type == 'c' || f->type == 'C')
	{
		f->string = ft_strnew(1);
		cnt = ft_manage_char(args, f);
	}
	else if (f->type == 'f' || f->type == 'F')
		cnt = ft_manage_float(args, f);
	else if (f->type == 'p')
		cnt = ft_manage_pointer(f, ft_strlen(f->string));
	else
		cnt = ft_manage_int(f, ft_strlen(f->string));
	return (cnt);
}

int		ft_is_type(char type)
{
	if (type == 'x' || type == 'X' || type == 'u' || type == 'o'
		|| type == 'p' || type == 'U' || type == 'O' || type == 'c'
		|| type == 'd' || type == 'i' || type == 'D' || type == 's'
		|| type == 'f' || type == 'C' || type == 'S' || type == 'F')
		return (1);
	return (0);
}

int		ft_parse_format(char *str, va_list args, int *i, t_format *f)
{
	int	f_start;
	int	f_end;
	int	cnt;

	*i = *i + 1;
	f_start = *i;
	f_end = f_start;
	if (!(f->type = ft_set_type(str, f, i, &f_end)))
		return (0);
	f->width = ft_set_width(str, f_start, *i, args);
	f->flags = ft_set_flags(str, f_start, *i);
	f->flags = (f->width >= 0 ? f->flags : ft_strjoin(f->flags, "-"));
	f->width = f->width < 0 ? -f->width : f->width;
	f->precision = ft_set_precision(str, f_start, *i, args);
	f->mod = ft_set_mod(str, f_start, *i);
	if (ft_is_type(f->type))
	{
		cnt = ft_take_arg(args, f);
		ft_strdel(&f->string);
	}
	else
		cnt = ft_manage_other(f);
	return (cnt);
}

int		ft_print_and_offset(const char *str, int start, int *cnt)
{
	int		stop;
	int		i;
	int		j;
	char	*str_to_print;

	i = start;
	while (str[i] && str[i] != '%')
		i++;
	stop = i;
	str_to_print = ft_strnew(i);
	i = start;
	j = 0;
	while (str[i] && str[i] != '%')
		str_to_print[j++] = str[i++];
	ft_putstr_unicode(str_to_print);
	*cnt += ft_strlen(str_to_print);
	ft_strdel(&str_to_print);
	return (stop);
}

int		ft_printf(const char *format, ...)
{
	int			i;
	int			cnt;
	int			len;
	t_format	*format_str;
	va_list		args;

	va_start(args, format);
	cnt = 0;
	i = -1;
	len = ft_strlen(format);
	while (++i < len)
	{
		i = ft_print_and_offset(format, i, &cnt);
		if (format[i] && format[i] == '%')
		{
			format_str = (t_format *)malloc(sizeof(t_format));
			format_str->string = NULL;
			cnt += ft_parse_format((char *)format, args, &i, format_str);
			if (format_str->flags)
				ft_strdel(&format_str->flags);
			free(format_str);
		}
	}
	va_end(args);
	return (cnt);
}
