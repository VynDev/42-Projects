/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  utility.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:16:49 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/15 14:36:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void		delete_tab(char **tab)
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

int		color(int r, int g, int b)
{
	int		color;

	color = 0x000000;
	color = color | (r << 16);
	color = color | (g << 8);
	color = color | (b << 0);
	return (color);
}
