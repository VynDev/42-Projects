/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:22:47 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 14:27:46 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			get_maxlinklen(t_list *lst)
{
	int		max;
	t_info	*info;

	max = 1;
	while (lst)
	{
		info = lst->content;
		if (ft_nbrlen(info->st.st_nlink) > max)
			max = ft_nbrlen(info->st.st_nlink);
		lst = lst->next;
	}
	return (max);
}

int			get_maxsizelen(t_list *lst)
{
	int		max;
	int		has_dev;
	t_info	*info;

	max = 1;
	has_dev = 0;
	while (lst)
	{
		info = lst->content;
		if (has_dev == 0 && (S_ISCHR(info->st.st_mode)
					|| S_ISBLK(info->st.st_mode)))
			has_dev = 1;
		if (ft_nbrlen(info->st.st_size) > max)
			max = ft_nbrlen(info->st.st_size);
		lst = lst->next;
	}
	return (has_dev ? 8 : max);
}

int			get_maxuserlen(t_list *lst)
{
	size_t	max;
	t_info	*info;

	max = 1;
	while (lst)
	{
		info = lst->content;
		if (ft_strlen(info->username) > max)
			max = ft_strlen(info->username);
		lst = lst->next;
	}
	return (max);
}

int			get_usedblock(t_list *lst)
{
	int		nb;
	t_info	*info;

	nb = 0;
	while (lst)
	{
		info = lst->content;
		nb = nb + info->st.st_blocks;
		lst = lst->next;
	}
	return (nb);
}

int			get_maxgrplen(t_list *lst)
{
	size_t	max;
	t_info	*info;

	max = 1;
	while (lst)
	{
		info = lst->content;
		if (ft_strlen(info->grpname) > max)
			max = ft_strlen(info->grpname);
		lst = lst->next;
	}
	return (max);
}
