/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:23:48 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 14:23:49 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	str = (char *)s;
	size = ft_strlen(str);
	while (i <= size)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}
