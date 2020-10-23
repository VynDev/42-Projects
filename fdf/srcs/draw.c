/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:16:49 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/15 14:36:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void		draw_pixel(t_data *data, t_segment s, t_segment pos, int i)
{
	int		a;
	t_map	*map;

	map = data->map;
	if (s.h2 > s.h1 && abs(s.x2-s.x1) > abs(s.y2-s.y1))
		a = (int)(((float)255 * ((float)s.h1/(float)map->h_max))
			+ ((float)255 * ((((float)s.h2 - (float)s.h1)/(float)map->h_max)
				* ((float)i/(float)abs(s.x2-s.x1)))));
	else if (abs(s.x2-s.x1) > abs(s.y2-s.y1))
		a = (int)(((float)255 * ((float)s.h1/(float)map->h_max))
			- ((float)255 * ((((float)s.h1 - (float)s.h2)/(float)map->h_max)
				* ((float)i/(float)abs(s.x2-s.x1)))));
	else if (s.h2 > s.h1)
		a = (int)(((float)255 * ((float)s.h1/(float)map->h_max))
			+ ((float)255 * ((((float)s.h2 - (float)s.h1)/(float)map->h_max)
				* ((float)i/(float)abs(s.y2-s.y1)))));
	else
		a = (int)(((float)255 * ((float)s.h1/(float)map->h_max))
			- ((float)255 * ((((float)s.h1 - (float)s.h2)/(float)map->h_max)
				* ((float)i/(float)abs(s.y2-s.y1)))));
	mlx_pixel_put(data->mlx,
		data->win, pos.x1, pos.y1, color(0 + abs(a), 0 + abs(a), 255));
}

static void		draw_dx(t_data *data, t_segment s, int erreur)
{
	int			i;
	t_segment	pos;

	pos.x1 = s.x1;
	pos.y1 = s.y1;
	i = 0;
	while (i < abs(s.x2-s.x1))
	{
		pos.x1 += s.x1 < s.x2 ? 1 : -1;
		erreur += abs(s.y2-s.y1);
		if(erreur > abs(s.x2-s.x1))
		{
			erreur -= abs(s.x2-s.x1);
			pos.y1 += s.y1 < s.y2 ? 1 : -1;
		}
		draw_pixel(data, s, pos, i);
		++i;
	}
}

static void		draw_dy(t_data *data, t_segment s, int erreur)
{
	int			i;
	t_segment	pos;

	pos.x1 = s.x1;
	pos.y1 = s.y1;
	i = 0;
	while (i < abs(s.y2-s.y1))
	{
		pos.y1 += s.y1 < s.y2 ? 1 : -1;
		erreur += abs(s.x2-s.x1);
		if(erreur > abs(s.y2-s.y1))
		{
			erreur -= abs(s.y2-s.y1);
			pos.x1 += s.x1 < s.x2 ? 1 : -1;
		}
		draw_pixel(data, s, pos, i);
		++i;
	}
}

void			draw_segment(t_data *data, t_segment s, t_map *map)
{
	int		erreur;
	int		a;

	a = (int)((float)255 * ((float)s.h1 / (float)map->h_max));
	mlx_pixel_put(data->mlx, data->win, s.x1, s.y1, color(0 + a, 0 + a, 255));
	if(abs(s.x2-s.x1) > abs(s.y2-s.y1))
	{
		erreur = abs(s.x2-s.x1) / 2;
		draw_dx(data, s, erreur);
	}
	else
	{
		erreur = abs(s.y2-s.y1) / 2;
		draw_dy(data, s, erreur);
	}
	mlx_pixel_put(data->mlx, data->win, s.x2, s.y2, color(0 + a, 0 + a, 255));
}
