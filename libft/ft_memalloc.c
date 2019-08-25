/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:44:40 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/26 14:44:41 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*array;

	array = (char *)malloc(sizeof(char) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < size)
		array[i++] = '\0';
	return (array);
}
