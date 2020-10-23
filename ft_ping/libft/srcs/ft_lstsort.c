/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:25:44 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/06 12:19:11 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(t_list *lst)
{
	char	*temp;
	int		i_temp;

	temp = lst->content;
	lst->content = lst->next->content;
	lst->next->content = temp;
	i_temp = lst->content_size;
	lst->content_size = lst->next->content_size;
	lst->next->content_size = i_temp;
}

void		ft_lstsort(t_list *lst, int (*f)(t_list *lst))
{
	t_list	*root;
	int		ok;

	ok = 0;
	root = lst;
	while (lst)
	{
		if (lst->next)
		{
			if ((*f)(lst))
			{
				swap(lst);
				ok = 1;
			}
			lst = lst->next;
		}
		else if (ok != 0)
		{
			lst = root;
			ok = 0;
		}
		else
			return ;
	}
}
