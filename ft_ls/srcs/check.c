/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:21:51 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:21:57 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_arg(char c)
{
	int		i;
	char	*charset;

	charset = "-GRalrt1";
	i = 0;
	while (i < 8)
	{
		if (charset[i] == c)
			return (1);
		++i;
	}
	return (0);
}

int		arg_exist(t_list *args_list, char c)
{
	while (args_list)
	{
		if (*(char *)(args_list->content) == c)
			return (1);
		args_list = args_list->next;
	}
	return (0);
}

int		is_dir(t_info *info)
{
	if (S_ISDIR(info->st.st_mode))
		return (1);
	return (0);
}

int		is_dirlink(t_info *info)
{
	if (!info->link_info)
		return (0);
	if (S_ISDIR(info->link_info->st.st_mode))
		return (1);
	return (0);
}
