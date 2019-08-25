/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:29:52 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/24 17:29:53 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*source;
	char	*destination;
	size_t	i;

	i = -1;
	source = (char*)src;
	destination = (char*)dest;
	if (source < destination)
	{
		while ((int)(--len) >= 0)
			destination[len] = source[len];
	}
	else
	{
		while (++i < len)
			destination[i] = source[i];
	}
	return (dest);
}
