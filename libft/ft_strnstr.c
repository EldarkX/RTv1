/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:51:39 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 14:51:40 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *str, const char *sub_str, size_t len)
{
	size_t len2;

	if (*sub_str == '\0')
		return ((char*)str);
	len2 = ft_strlen(sub_str);
	while (*str != '\0' && len-- >= len2)
	{
		if (*str == *sub_str && ft_memcmp(str, sub_str, len2) == 0)
			return ((char*)str);
		str++;
	}
	return (NULL);
}
