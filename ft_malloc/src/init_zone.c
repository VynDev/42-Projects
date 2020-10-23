#include "ft_malloc.h"

void	init_zone(void *zone, int nb, int size)
{
	(void)nb;(void)size;

	((t_alloc_header *)zone)->size = 0;
	((t_alloc_header *)zone)->previous = NULL;
	((t_alloc_header *)zone)->next = NULL;
}