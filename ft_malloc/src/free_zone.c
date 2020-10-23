#include "ft_malloc.h"

void			free_zone(t_alloc_header *header)
{
	if (!header)
		return ;
	header->size = 0;
}