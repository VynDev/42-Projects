/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:22:08 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:22:11 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	delete_tab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (*(tab + i) != 0)
	{
		free(*(tab + i));
		++i;
	}
	free(*(tab + i));
	free(tab);
}

void	del_info(void *ptr, size_t size)
{
	t_info	*info;

	if (!ptr)
		return ;
	info = ptr;
	if (info->name)
		free(info->name);
	if (info->path)
		free(info->path);
	if (info->link)
		free(info->link);
	if (info->link_info)
		del_info(info->link_info, size);
	if (info->username)
		free(info->username);
	if (info->grpname)
		free(info->grpname);
	if (ptr)
		free(ptr);
}

void	del_nothing(void *ptr, size_t size)
{
	(void)size;
	if (ptr)
		free(ptr);
}

void	del_path(void *ptr, size_t size)
{
	(void)size;
	if (ptr)
		free(ptr);
}
