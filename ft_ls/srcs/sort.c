/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:24:51 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:35:04 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	lstsort_str1(t_list *lst)
{
	if (ft_strcmp(((t_info *)lst->content)->name,
				((t_info *)lst->next->content)->name) < 0)
		return (1);
	return (0);
}

static int	lstsort_str2(t_list *lst)
{
	if (ft_strcmp(((t_info *)lst->content)->name,
				((t_info *)lst->next->content)->name) > 0)
		return (1);
	return (0);
}

static int	lstsort_time1(t_list *lst)
{
	if (((t_info *)lst->content)->st.st_mtimespec.tv_sec
			< ((t_info *)lst->next->content)->st.st_mtimespec.tv_sec)
		return (1);
	if (((t_info *)lst->content)->st.st_mtimespec.tv_sec
			== ((t_info *)lst->next->content)->st.st_mtimespec.tv_sec)
	{
		if (ft_strcmp(((t_info *)lst->content)->name,
					((t_info *)lst->next->content)->name) > 0)
			return (1);
	}
	return (0);
}

static int	lstsort_time2(t_list *lst)
{
	if (((t_info *)lst->content)->st.st_mtimespec.tv_sec
			> ((t_info *)lst->next->content)->st.st_mtimespec.tv_sec)
		return (1);
	if (((t_info *)lst->content)->st.st_mtimespec.tv_sec
			== ((t_info *)lst->next->content)->st.st_mtimespec.tv_sec)
	{
		if (ft_strcmp(((t_info *)lst->content)->name,
					((t_info *)lst->next->content)->name) < 0)
			return (1);
	}
	return (0);
}

void		sort_list(t_list *lst, t_list *args_list)
{
	if (arg_exist(args_list, 'r') && !arg_exist(args_list, 't'))
		ft_lstsort(lst, &lstsort_str1);
	else if (!arg_exist(args_list, 't'))
		ft_lstsort(lst, &lstsort_str2);
	else if (!arg_exist(args_list, 'r') && arg_exist(args_list, 't'))
		ft_lstsort(lst, &lstsort_time1);
	else if (arg_exist(args_list, 't'))
		ft_lstsort(lst, &lstsort_time2);
}
