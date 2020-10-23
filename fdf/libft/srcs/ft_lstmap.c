/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:25:51 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:37:50 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new_list = (*f)(lst);
	temp = new_list;
	while (lst)
	{
		if (lst->next)
		{
			temp->next = (*f)(lst->next);
			if (!temp->next)
				return (NULL);
		}
		lst = lst->next;
		temp = temp->next;
	}
	return (new_list);
}
