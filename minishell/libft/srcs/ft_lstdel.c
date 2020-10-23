/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:25:21 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:25:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	if (!alst)
		return ;
	while (*alst)
	{
		if ((*alst)->next)
			next = (*alst)->next;
		else
			next = NULL;
		ft_lstdelone(alst, del);
		*alst = next;
	}
}
