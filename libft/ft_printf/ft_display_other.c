/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:52:01 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/30 13:52:02 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_manage_other(t_format *f)
{
	int space_cnt;
	int cnt;

	space_cnt = f->width - 1;
	cnt = 0;
	if (ft_strchr(f->flags, '-'))
	{
		cnt += ft_putchar_unicode(f->type);
		while (space_cnt-- > 0 && ++cnt)
			ft_putchar_unicode(' ');
	}
	else
	{
		while (space_cnt-- > 0 && ++cnt)
			ft_putchar_unicode(ft_strchr(f->flags, '0') ? '0' : ' ');
		cnt += ft_putchar_unicode(f->type);
	}
	return (cnt);
}
