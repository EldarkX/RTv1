/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:18:36 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 12:18:37 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t len1;
	size_t len2;

	if (ft_strlen(dest) < size)
		len1 = ft_strlen(dest);
	else
		len1 = size;
	len2 = ft_strlen(src);
	if (len2 < size - len1)
		ft_strncat(dest, src, len2 + 1);
	else if (size > len1)
	{
		ft_strncat(dest, src, size - len1 - 1);
		dest[size - 1] = '\0';
	}
	return (len1 + len2);
}
