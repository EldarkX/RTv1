/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:16:09 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 17:16:10 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	j = 0;
	while ((s[j] == ' ' || s[j] == '\t') || s[j] == '\n')
		j++;
	k = i - 1;
	while (s[k] == ' ' || s[k] == '\t' || s[k] == '\n')
		k--;
	i = j;
	while (i < k + 1)
		i++;
	if (!(str = ft_strnew(i - j)))
		return (NULL);
	i = 0;
	while (j < k + 1)
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}
