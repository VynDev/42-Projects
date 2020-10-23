#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# define WIDTH 1800
# define HEIGHT 1000

typedef struct s_map
{
    int         x;
    int         y;
    int         h_max;
    int         **height;
}               t_map;

typedef struct s_data
{
    void		*mlx;
    void 		*win;
    t_map       *map;
    int         size;
    int         amp;
    int         x_decal;
    int         y_decal;
    int         x_persp;
    int         mode;
}				t_data;

typedef struct s_segment
{
    int			x1;
    int			y1;
    int			h1;
	int			x2;
    int			y2;
    int			h2;
}				t_segment;

int    			 key_pressed(int key, void *data);

void			draw_segment(t_data *data, t_segment s, t_map *map);

t_map			*get_map(const char *file);

int				color(int r, int g, int b);

void            show_map_iso(t_map *map, t_data *data);

void            set_center(t_map *map, t_data *data);

void            set_size(int size, t_map *map, t_data *data);

void            delete_tab(char **tab);

#endif 
