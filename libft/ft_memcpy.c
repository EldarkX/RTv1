/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:10:22 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/24 16:43:21 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*new_dst;
	char	*c_src;

	i = 0;
	new_dst = (char *)dst;
	c_src = (char *)src;
	while (i < n)
	{
		new_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}
