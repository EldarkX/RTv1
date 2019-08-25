/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:07:33 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/25 14:07:34 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	j = ft_strlen(s1);
	i = 0;
	while (s2[i] != '\0' && i < len)
		s1[j++] = s2[i++];
	s1[j] = '\0';
	return (s1);
}
