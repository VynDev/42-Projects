/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:23:14 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:31:53 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_type(t_info *info)
{
	if (info->link != NULL)
		ft_printf("l");
	else if (S_ISREG(info->st.st_mode))
		ft_printf("-");
	else if (S_ISDIR(info->st.st_mode))
		ft_printf("d");
	else if (S_ISCHR(info->st.st_mode))
		ft_printf("c");
	else if (S_ISBLK(info->st.st_mode))
		ft_printf("b");
	else if (S_ISWHT(info->st.st_mode))
		ft_printf("w");
	else if (S_ISSOCK(info->st.st_mode))
		ft_printf("s");
	else if (S_ISFIFO(info->st.st_mode))
		ft_printf("i");
	else
		ft_printf("{red}NOT SUPPORTED{eoc}");
}

char	*set_access(int access, char *path, char *access_char)
{
	access_char[0] = (access & S_IRUSR) ? 'r' : '-';
	access_char[1] = (access & S_IWUSR) ? 'w' : '-';
	if (access & S_ISUID)
		access_char[2] = (access & S_IXUSR) ? 's' : 'S';
	else
		access_char[2] = (access & S_IXUSR) ? 'x' : '-';
	access_char[3] = (access & S_IRGRP) ? 'r' : '-';
	access_char[4] = (access & S_IWGRP) ? 'w' : '-';
	if (access & S_ISGID)
		access_char[5] = (access & S_IXGRP) ? 's' : 'S';
	else
		access_char[5] = (access & S_IXGRP) ? 'x' : '-';
	access_char[6] = (access & S_IROTH) ? 'r' : '-';
	access_char[7] = (access & S_IWOTH) ? 'w' : '-';
	if (access & S_ISVTX)
		access_char[8] = (access & S_IXOTH) ? 't' : 'T';
	else
		access_char[8] = (access & S_IXOTH) ? 'x' : '-';
	access_char[9] = listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0 ? '@' : ' ';
	access_char[10] = '\0';
	return (access_char);
}

int		alternate_print(t_info *info,
		char *info_time, char *access_char, int *maxlen)
{
	ft_printf("%s %*d %-*s  %-*s  %3d, %3d %s %s%s",
	access_char,
	maxlen[0], info->st.st_nlink,
	maxlen[1], info->username,
	maxlen[2], info->grpname,
	MAJOR(info->st.st_rdev), MINOR(info->st.st_rdev),
	info_time,
	info->name,
	info->link == NULL ? "\n" : "");
	free(info_time);
	return (1);
}

int		print_info(t_info *info, int *maxlen)
{
	char	*info_time;
	char	access_char[12];

	info_time = get_time(info->st.st_mtimespec.tv_sec);
	print_type(info);
	set_access(info->st.st_mode, info->path, access_char);
	if (S_ISCHR(info->st.st_mode) || S_ISBLK(info->st.st_mode))
		return (alternate_print(info, info_time, access_char, maxlen));
	ft_printf("%s %*d %-*s  %-*s  %*llu %s %s%s",
	access_char,
	maxlen[0], info->st.st_nlink,
	maxlen[1], info->username,
	maxlen[2], info->grpname,
	maxlen[3], info->st.st_size,
	info_time,
	info->name,
	info->link == NULL ? "\n" : "");
	if (info->link != NULL)
		ft_printf(" -> %s\n", info->link);
	free(info_time);
	return (1);
}

t_list	*print_dir(t_list *info_list, t_list *args_list)
{
	t_info			*info;
	t_list			*rec;
	int				maxlen[4];

	if (arg_exist(args_list, 'l'))
		get_maxlen(info_list, maxlen);
	rec = NULL;
	while (info_list)
	{
		info = info_list->content;
		print_color(info, args_list);
		if (S_ISDIR(info->st.st_mode) && arg_exist(args_list, 'R')
				&& !ft_strequ(info->name, ".") && !ft_strequ(info->name, ".."))
			ft_lstaddback(&rec, ft_lstnew(info, sizeof(t_info)));
		if (arg_exist(args_list, 'l'))
			print_info(info, maxlen);
		else
			ft_printf("%s\n", info->name);
		reset_color(info, args_list);
		info_list = info_list->next;
	}
	return (rec);
}
