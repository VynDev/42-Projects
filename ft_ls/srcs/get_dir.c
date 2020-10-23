/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:22:27 by xesnault          #+#    #+#             */
/*   Updated: 2017/02/13 12:48:32 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			fill_infolist(struct dirent *dp,
		char *dir_name, t_list **info_list, int hiden)
{
	t_info	*info;

	if ((info = get_info(dir_name, dp->d_name)) == NULL)
		return (0);
	if (hiden || (!hiden && !(info->name[0] == '.')))
	{
		ft_lstadd(info_list, ft_lstnew(info, sizeof(t_info)));
		free(info);
	}
	else
		del_info(info, sizeof(t_info));
	return (1);
}

t_list		*get_dir(char *dir_name, int hiden)
{
	struct dirent	*dp;
	DIR				*dir;
	t_list			*info_list;
	char			*tmp;

	info_list = NULL;
	dir = opendir(dir_name);
	if (!dir)
	{
		tmp = ft_strrchr(dir_name, '/');
		error(tmp ? tmp + 1 : dir_name);
		return (NULL);
	}
	while ((dp = readdir(dir)) != NULL)
	{
		if (!fill_infolist(dp, dir_name, &info_list, hiden))
			return (NULL);
	}
	closedir(dir);
	return (info_list);
}
