/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:25:34 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:56:08 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static int	set_check(t_list **alst,
		t_list **last, t_list **current, t_list **after)
{
	*last = NULL;
	*current = *alst;
	*after = (*current)->next;
	if (!alst)
		return (0);
	return (1);
}

void		ft_lstdelif(t_list **alst, int (*del)(void *, void *), void *data)
{
	t_list	*last;
	t_list	*current;
	t_list	*after;

	if (!set_check(alst, &last, &current, &after))
		return ;
	while (current)
	{
		if ((*del)(current->content, data))
		{
			if (last)
				last->next = after;
			else
				*alst = after;
			free(current->content);
			current = after;
		}
		else
		{
			last = current;
			current = current->next;
			if (current)
				after = current->next;
		}
	}
}
