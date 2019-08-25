/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:47:58 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 13:48:44 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (!src[i])
		{
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
			break ;
		}
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
