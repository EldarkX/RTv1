/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:44:49 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/27 14:44:50 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_diplay_string(t_format *f, size_t len, size_t i)
{
	size_t	j;
	int		cnt;
	char	*str;

	len = (f->precision < (int)len && f->precision != -1 ? f->precision : len);
	str = ft_strnew((len >= (size_t)f->width) ? len : f->width);
	ft_memset(str, (ft_strchr(f->flags, '0') && !ft_strchr(f->flags, '-') ?
			'0' : ' '), len >= (size_t)f->width ? len : f->width);
	i = -1;
	if (ft_strchr(f->flags, '-'))
		while (++i < len)
			str[i] = f->string[i];
	else
	{
		i = ((size_t)f->width <= len) ? 0 : f->width - len;
		j = 0;
		while (j < len)
			str[i++] = f->string[j++];
	}
	ft_strdel(&f->string);
	f->string = ft_strdup(str);
	ft_strdel(&str);
	cnt = ft_putstr_unicode(f->string);
	return (cnt);
}

int		ft_manage_s(va_list args, t_format *f)
{
	char	*s;
	int		cnt;

	s = va_arg(args, char *);
	if (!s)
	{
		f->string = NULL;
		f->string = ft_strdup("(null)");
	}
	else
		f->string = ft_strdup(s);
	cnt = ft_diplay_string(f, ft_strlen(f->string), -1);
	return (cnt);
}
