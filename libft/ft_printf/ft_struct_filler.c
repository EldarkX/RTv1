/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_filler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:17:38 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/26 10:17:40 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	ft_set_type(char *str, t_format *f, int *i, int *format_end)
{
	char	t;

	f->flags = NULL;
	while (str[*i] && str[*i] != '%')
	{
		t = str[*i];
		if ((ft_isalpha(t) || (t >= 33 && t <= 41) || t == 44 || (t >= 123
			&& t < 127) || (t >= 91 && t <= 96) || t == 47) && t != 35 &&
			!ft_is_mode_width(t))
		{
			*format_end = *i;
			return (t);
		}
		*i = *i + 1;
	}
	t = str[*i];
	if (t == '%')
	{
		*format_end = *i;
		return (t);
	}
	return (0);
}

char	*ft_set_flags(char *str, int format_start, int format_end)
{
	char	*flags;
	int		i;

	i = 0;
	flags = ft_strnew(5);
	flags[5] = '\0';
	while (format_start < format_end)
	{
		if ((str[format_start] == '-') && !ft_strchr(flags, '-'))
			flags[i++] = '-';
		else if (str[format_start] == '+' && !ft_strchr(flags, '+'))
			flags[i++] = '+';
		else if (str[format_start] == ' ' && !ft_strchr(flags, ' '))
			flags[i++] = ' ';
		else if (str[format_start] == '#' && !ft_strchr(flags, '#'))
			flags[i++] = '#';
		else if (str[format_start] == '0' && str[format_start - 1] != '.'
			&& !ft_strchr(flags, '0') &&
				!ft_isdigit(str[format_start - 1]))
			flags[i++] = '0';
		format_start++;
	}
	return (flags);
}

int		ft_set_width(char *str, int format_start, int format_end, va_list args)
{
	int		width;
	char	*a;

	width = 0;
	while (format_start < format_end)
	{
		if (str[format_start - 1] == '.' && ft_isdigit(str[format_start]))
			while (format_start < format_end && ft_isdigit(str[format_start]))
				format_start++;
		else if (ft_isdigit(str[format_start]) && str[format_start] != '0')
		{
			a = ft_strsub(str, format_start, ft_strlen(str));
			width = ft_atoi(a);
			ft_strdel(&a);
			format_start += ft_digit_cnt_base(width, 10);
		}
		else if (str[format_start] == '*' && str[format_start - 1] != '.')
		{
			width = va_arg(args, int);
			format_start++;
		}
		else
			format_start++;
	}
	return (width);
}

int		ft_set_precision(char *str, int start, int format_end,
		va_list args)
{
	int		precision;
	char	*a;

	precision = -1;
	while (start < format_end)
	{
		if (ft_isdigit(str[start]) && str[start - 1] == '.')
		{
			a = ft_strsub(str, start, format_end - start);
			precision = ft_atoi(a);
			ft_strdel(&a);
		}
		else if (str[start] == '*' && str[start - 1] == '.')
			precision = va_arg(args, int);
		else if (str[start] == '.')
			precision = 0;
		start++;
	}
	return (precision >= -1 ? precision : -1);
}

int		ft_set_mod(char *str, int format_start, int format_end)
{
	int	mode;

	mode = -1;
	while (format_start < format_end)
	{
		if (str[format_start] == 'h' && str[format_start + 1] == 'h')
			mode = (mode < 0) ? 0 : mode;
		else if (str[format_start] == 'h' && str[format_start - 1] != 'h')
			mode = (mode < 1) ? 1 : mode;
		else if (str[format_start] == 'l' && str[format_start - 1] != 'l')
			mode = (mode < 2) ? 2 : mode;
		else if (str[format_start] == 'l' && str[format_start + 1] == 'l')
			mode = (mode < 3) ? 3 : mode;
		else if (str[format_start] == 'j')
			mode = (mode < 4) ? 4 : mode;
		else if (str[format_start] == 'z')
			mode = (mode < 5) ? 5 : mode;
		else if (str[format_start] == 'L')
			mode = (mode < 6) ? 6 : mode;
		format_start++;
	}
	return (mode);
}
