/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:16:49 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/15 14:36:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void		draw_right(t_map *map, t_data *data, int x, int y)
{
	t_segment	s;

	if (x == map->x - 1)
		return ;
	s.x1 = data->x_decal + ((x * data->size) - (y * data->size)) * 1;
	s.y1 = data->y_decal + ((x * (data->size) / 2) + (y * (data->size / 2)) - (map->height[y][x] * data->amp)) * 1;
	s.x2 = data->x_decal + (((x + 1) * data->size) - (y * data->size)) * 1;
	s.y2 = data->y_decal + (((x + 1) * (data->size) / 2) + (y * (data->size / 2)) - (map->height[y][x + 1] * data->amp)) * 1;
	s.h1 = map->height[y][x];
	s.h2 = map->height[y][x + 1];
	draw_segment(data, s, map);
}

static void		draw_bot(t_map *map, t_data *data, int x, int y)
{
	t_segment	s;

	if (y == map->y - 1)
		return ;
	s.x1 = data->x_decal + ((x * data->size) - (y * data->size)) * 1;
	s.y1 = data->y_decal + ((x * (data->size) / 2) + (y * (data->size / 2)) - (map->height[y][x] * data->amp)) * 1;
	s.x2 = data->x_decal + ((x * data->size) - ((y + 1) * data->size)) * 1;
	s.y2 = data->y_decal + ((x * (data->size) / 2) + ((y + 1) * (data->size / 2)) - (map->height[y + 1][x] * data->amp)) * 1;
	s.h1 = map->height[y][x];
	s.h2 = map->height[y + 1][x];
	draw_segment(data, s, map);
}

void			show_map_iso(t_map *map, t_data *data)
{
	int		x;
	int		y;

	y = 0;
	mlx_clear_window(data->mlx, data->win);
	set_center(map, data);
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			draw_right(map, data, x, y);
			draw_bot(map, data, x, y);
			++x;
		}
		++y;
	}
}