/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:04:42 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/28 14:04:43 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if (!(node = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
		node->content = NULL;
	else
	{
		node->content_size = content_size;
		node->content = malloc(content_size);
		ft_memcpy(node->content, content, content_size);
	}
	node->next = NULL;
	return (node);
}
