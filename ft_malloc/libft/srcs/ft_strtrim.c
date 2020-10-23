/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:33:21 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 15:58:57 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int		find_first_char(char const *s)
{
	int		i;

	i = 0;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	return (i);
}

static int		find_last_char(char const *s)
{
	int		i;
	int		last;

	i = 0;
	last = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			last = i;
		i++;
	}
	return (last);
}

char			*ft_strtrim(char const *s)
{
	char	*returned_char;

	if (!s)
		return (NULL);
	if ((unsigned long)find_first_char(s) == ft_strlen(s))
		return (ft_strdup(""));
	returned_char = ft_strsub(s, find_first_char(s),
				find_last_char(s) - find_first_char(s) + 1);
	return (returned_char);
}
