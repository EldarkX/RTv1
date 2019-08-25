/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:41:30 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 16:41:31 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (s[start + len - 1] == '\0')
	{
		if (!(str = ft_strnew(len - 1)))
			return (NULL);
	}
	else
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
	}
	i = 0;
	while (len--)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	if (str[i] != '\0')
		str[i] = '\0';
	return (str);
}
