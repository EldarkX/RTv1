/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:31:41 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 16:31:43 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t i;
	size_t j;

	if (!s1 && !s2)
		return (1);
	else if (!s1 && s2)
		return (0);
	else if (s1 && !s2)
		return (0);
	else
	{
		i = ft_strlen((char *)s1);
		j = ft_strlen((char *)s2);
		if (i == j)
		{
			i = 0;
			while (s1[i] == s2[i])
			{
				if (i == j)
					return (1);
				i++;
			}
		}
		return (0);
	}
}
