/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:22:35 by xesnault          #+#    #+#             */
/*   Updated: 2017/02/13 12:49:25 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		do_lstat(t_info *info, char *tmp, int ret)
{
	char	*temp_path;
	char	*tmp2;
	char	*tmp3;

	tmp[ret] = '\0';
	info->link = ft_strdup(tmp);
	temp_path = ft_strdup(info->path);
	tmp2 = ft_strrchr(temp_path, '/');
	if (tmp2 && *(tmp2 + 1) != '\0')
		*(tmp2 + 1) = '\0';
	else
		*(temp_path) = '\0';
	tmp3 = temp_path;
	temp_path = ft_strjoin(temp_path, info->link);
	free(tmp3);
	free(temp_path);
	info->link_info = get_info(NULL, temp_path);
	if (lstat(info->path, &(info->st)) < 0)
		return (0);
	return (1);
}

static int		do_stat(t_info *info)
{
	info->link = NULL;
	info->link_info = NULL;
	if (stat(info->path, &(info->st)) < 0)
	{
		if (info->name)
			free(info->name);
		if (info->path)
			free(info->path);
		free(info);
		return (0);
	}
	return (1);
}

static void		set_path(t_info *info, char *dir_name, char *file)
{
	char	*temp;

	if (ft_strcmp(dir_name, "/") == 0)
	{
		info->path = ft_strdup("/");
		temp = info->path;
		info->path = ft_strjoin(info->path, file);
	}
	else
	{
		info->path = ft_strjoin(dir_name, "/");
		temp = info->path;
		info->path = ft_strjoin(info->path, file);
	}
	free(temp);
}

static void		get_usrandgrp(t_info *info)
{
	struct passwd	*pw;
	struct group	*grp;

	pw = NULL;
	grp = NULL;
	pw = getpwuid(info->st.st_uid);
	if (pw && pw->pw_name)
		info->username = ft_strdup(pw->pw_name);
	else
		info->username = ft_itoa(info->st.st_uid);
	grp = getgrgid(info->st.st_gid);
	if (grp && grp->gr_name)
		info->grpname = ft_strdup(grp->gr_name);
	else
		info->grpname = ft_itoa(info->st.st_gid);
}

t_info			*get_info(char *dir_name, char *file)
{
	t_info	*info;
	char	tmp[256];
	int		ret;

	if ((info = (t_info *)custom_malloc(sizeof(t_info))) == NULL)
		return (NULL);
	info->name = ft_strdup(file);
	if (dir_name)
		set_path(info, dir_name, file);
	else
		info->path = ft_strdup(file);
	if ((ret = readlink(info->path, tmp, 256)) != -1)
	{
		if (!do_lstat(info, tmp, ret))
			return (NULL);
	}
	else
	{
		if (!do_stat(info))
			return (NULL);
	}
	get_usrandgrp(info);
	return (info);
}
