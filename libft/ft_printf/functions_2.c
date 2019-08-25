/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:10:01 by aantropo          #+#    #+#             */
/*   Updated: 2018/12/10 16:10:04 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char			*ft_choose_prefix(t_format *f)
{
	char *str;

	if (f->type == 'o')
		str = ft_strdup("0");
	else if (f->type == 'x')
		str = ft_strdup("0x");
	else if (f->type == 'X')
		str = ft_strdup("0X");
	else
		str = ft_strdup("\0");
	return (str);
}

char			*ft_add_prefix(t_format *f)
{
	char	*nstr;

	if (!ft_strcmp(f->string, "0") && !ft_strchr(f->flags, '+')
		&& !ft_strchr(f->flags, ' '))
		nstr = ft_strdup("\0");
	else if (f->string[0] == '-')
	{
		nstr = ft_strdup("-");
		ft_memmove(f->string, f->string + 1, ft_strlen(f->string));
	}
	else if (ft_strchr(f->flags, '+') && (f->type == 'd' || f->type == 'i'))
		nstr = ft_strdup("+");
	else if (ft_strchr(f->flags, ' ') && (f->type == 'd' || f->type == 'i'))
		nstr = ft_strdup(" ");
	else if (ft_strchr(f->flags, '#') && ft_strcmp(f->string, "0"))
		nstr = ft_choose_prefix(f);
	else
		nstr = ft_strdup("\0");
	return (nstr);
}

long double		ft_e(int size)
{
	long double e;

	e = 1;
	while (size--)
		e /= 10;
	return (e);
}

long double		ft_find_float(int precision, long double fp, long double e)
{
	int			ip;
	long double tmp;

	tmp = fp - (uintmax_t)fp;
	ip = 1;
	while (ip > 0 && precision--)
	{
		tmp *= 10;
		ip = (uintmax_t)tmp;
		tmp -= ip;
	}
	if ((int)(tmp * 10) >= 5)
		fp += e;
	return (fp);
}
