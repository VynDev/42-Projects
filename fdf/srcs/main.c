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

void		free_map(t_map *map)
{
	int		y;

	y = 0;
	while (y < map->y)
	{
		free(*(map->height + y));
		++y;
	}
	free(map->height);
	free(map);
}

void		fdf_quit(t_data *data)
{
	free_map(data->map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data)
		free(data);
	ft_printf("{green}data freed, program will now exit...{eoc}\n");
	exit(0);
}

int			expose_hook(void *data)
{
	ft_printf("EXPOSE HOOK CALLED\n");
	show_map_iso(((t_data *)data)->map, data);
	return (0);
}

t_data		*init_data()
{
	t_data *data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
	{
		ft_printf("{red}initialization failed !{eoc}\n");
		exit(0);
	}
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf project");
	mlx_key_hook(data->win, &key_pressed, data);
	mlx_expose_hook(data->win, &expose_hook, data);
	ft_printf("{green}mlx initialized{eoc}\n");
	return (data);
}

int     	key_pressed(int key, void *data)
{
	ft_printf("The keycode is {red}%d{eoc}\n", key);
    if (key == 53)
        fdf_quit(data);
    else if (key == 126) 
    {
		(((t_data *)data)->size) = (((t_data *)data)->size) + 2;
		show_map_iso(((t_data *)data)->map, data);
    }
   	else if (key == 125 && ((t_data *)data)->size > 3) 
    {
		(((t_data *)data)->size) = (((t_data *)data)->size) - 2;
		show_map_iso(((t_data *)data)->map, data);
    }
    else if (key == 13) 
    {
		++(((t_data *)data)->amp);
		show_map_iso(((t_data *)data)->map, data);
    }
   	else if (key == 1 && ((t_data *)data)->amp > 1) 
    {
		--(((t_data *)data)->amp);
		show_map_iso(((t_data *)data)->map, data);
    }
    return (0);
}

int			main(int argc, char **argv)
{
	t_data	*data;
	t_map	*map;

	if (argc != 2)
	{
		ft_printf("{red}The file doesn't exist{eoc}\n");
		return (0);
	}
	data = init_data();
	map = get_map(argv[1]);
	data->map = map;
	data->mode = 2;
	data->amp = 1;
	set_size(-1, map, data);
	mlx_loop(data->mlx);
	return (0);
}


