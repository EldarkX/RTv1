/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:02:29 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 17:02:30 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen((char *)s1);
	size2 = ft_strlen((char *)s2);
	if (!(str = ft_strnew(size1 + size2)))
		return (NULL);
	i = 0;
	while (i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= size2)
	{
		str[i + size1] = s2[i];
		i++;
	}
	return (str);
}
