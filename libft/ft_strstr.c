/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:41:09 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 14:41:11 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *str, const char *sub_str)
{
	size_t	i;
	size_t	j;
	char	*str2;

	str2 = (char *)str;
	if (sub_str[0] == '\0')
		return (str2);
	i = -1;
	j = 0;
	while (str2[++i])
	{
		if (str2[i] == sub_str[j])
		{
			while (str2[i] == sub_str[j])
			{
				if (sub_str[j + 1] == '\0')
					return (str2 + i - j);
				j++;
				i++;
			}
			i -= j;
			j = 0;
		}
	}
	return (NULL);
}
