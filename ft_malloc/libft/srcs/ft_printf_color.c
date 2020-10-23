/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:43:10 by xesnault          #+#    #+#             */
/*   Updated: 2016/12/02 14:43:12 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char		*get_code(char *str, char **color, char **code, int *len_color)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (ft_strnequ(str + 1, color[i], ft_strlen(color[i])))
		{
			*len_color = ft_strlen(color[i]);
			return (ft_strdup(code[i]));
		}
		++i;
	}
	return (NULL);
}

static char		*get_color(char *str, int *len_color)
{
	char	*color[7];
	char	*code[7];

	color[0] = "red}";
	color[1] = "green}";
	color[2] = "yellow}";
	color[3] = "blue}";
	color[4] = "magenta}";
	color[5] = "cyan}";
	color[6] = "eoc}";
	code[0] = "\x1b[31m";
	code[1] = "\x1b[32m";
	code[2] = "\x1b[33m";
	code[3] = "\x1b[34m";
	code[4] = "\x1b[35m";
	code[5] = "\x1b[36m";
	code[6] = "\x1b[0m";
	return (get_code(str, color, code, len_color));
}

void			add_color(CCR format, t_pcursor *cur, int *len, char **str)
{
	char	*color;
	int		len_color;

	color = get_color((char *)format + cur->i, &len_color);
	if (color)
	{
		*len = add_to_finalstr(str, ft_strsub(format,
		cur->last, cur->i - cur->last), *len, cur->i - cur->last);
		*len = add_to_finalstr(str, color, *len, ft_strlen(color));
		cur->i += len_color + 1;
		cur->last = cur->i;
	}
	else
		++(cur->i);
}
