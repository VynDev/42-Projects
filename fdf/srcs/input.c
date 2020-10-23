/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:16:49 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/15 14:36:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int	count_nb_word(const char *str)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (str[i - 1] != '\0')
	{
		if ((str[i] == ' ' || str[i] == '\0') && str[i - 1] != ' ')
			++count;
		++i;
	}
	return (count);
}

static int	get_map_size(const char *file, t_map *map)
{
	char	*line;
	int		count;
	int		fd;
	int		len;

	map->x = -1;
	if (!file)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	count = 0;
	while (get_next_line(fd, &line))
	{
		len = count_nb_word(line);
		if (map->x == -1 || map->x > len)
			map->x = len;
		free(line);
		++count;
	}
	close(fd);
	map->y = count;
	return (1);
}

static int	fill_map(t_map *map, int fd)
{
	char	*line;
	char	**tab;
	int		i;
	int		j;

	map->h_max = 0;
	j = 0;
	while (get_next_line(fd, &line))
	{
		i = -1;
		tab = ft_strsplit(line, ' ');
		while (++i < map->x)
		{
			if (abs(ft_atoi(tab[i])) > map->h_max)
				map->h_max = abs(ft_atoi(tab[i]));
			map->height[j][i] = ft_atoi(tab[i]);
		}
		++j;
		delete_tab(tab);
		free(line);
	}
	close(fd);
	return (1);
}

t_map		*get_map(const char *file)
{
	int		i;
	t_map	*map;

	i = 0;

	map = (t_map *)malloc(sizeof(t_map));
	if (get_map_size(file, map) == 0)
		return (NULL);
	
	map->height = (int **)malloc(sizeof(int *) * map->y);
	
	while (i < map->y)
	{
		map->height[i] = (int *)malloc(sizeof(int) * map->x);
		++i;
	}
	fill_map(map, open(file, O_RDONLY));
	return (map);
}
