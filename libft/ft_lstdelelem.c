/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:13:52 by aantropo          #+#    #+#             */
/*   Updated: 2018/10/29 11:13:53 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdelelem(void *lst_elem, size_t elem_size)
{
	if (elem_size && lst_elem)
		ft_memdel(&(lst_elem));
}
