/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:16:49 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/15 14:36:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"


void		set_size(int size, t_map *map, t_data *data)
{
	if (size <= 1)
	{
		data->size = 1000 / ((map->x) + (map->y));
		data->size = data->size <= 1 ? 2 : data->size;
	}
	else
		data->size = size;

}

void		set_center(t_map *map, t_data *data)
{
	data->x_decal = (WIDTH / 2) + ((map->y * data->size) / 2) - ((map->x * data->size) / 2);
	data->y_decal = (HEIGHT / 2) - (((map->x * (data->size / 2)) + (map->y * (data->size / 2))) / 2);
	data->map = map;
}