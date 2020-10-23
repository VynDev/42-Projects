/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:22:18 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 15:58:57 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*get_time_ext(char *info_time)
{
	char	*returned;
	char	*tmp;
	char	**tab;

	returned = (char *)custom_malloc(sizeof(char ) * 32);
	tmp = ft_strrchr(info_time, ':');
	tab = ft_strsplit(tmp, ' ');
	if (!tab)
		exit(2);
	*(tmp - 6) = '\0';
	ft_strcpy(returned, ft_strchr(info_time, ' ') + 1);
	ft_strcat(returned, "  ");
	ft_strcat(returned, tab[1]);
	delete_tab(tab);
	return (returned);
}

char		*get_time(const time_t sec)
{
	char		*info_time;
	char		*tmp;
	time_t		t;

	time(&t);
	info_time = ctime(&sec);
	*(info_time + ft_strlen(info_time) - 1) = '\0';
	if (sec <= t && t - sec <= 15724800)
	{
		tmp = ft_strrchr(info_time, ':');
		*tmp = '\0';
		return (ft_strdup(ft_strchr(info_time, ' ') + 1));
	}
	else
		return (get_time_ext(info_time));
	return (NULL);
}

void		get_maxlen(t_list *lst, int *max)
{
	max[0] = get_maxlinklen(lst);
	max[1] = get_maxuserlen(lst);
	max[2] = get_maxgrplen(lst);
	max[3] = get_maxsizelen(lst);
}

int			get_slash(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == '/')
			++count;
		else
			return (count);
		++str;
	}
	return (count);
}
