/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:04:46 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/29 12:04:47 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*tmp;
	t_list	*head;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	if (!(new_list = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	head = new_list;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		new_list->next = ft_lstnew(tmp->content, tmp->content_size);
		new_list = new_list->next;
		lst = lst->next;
	}
	return (head);
}
