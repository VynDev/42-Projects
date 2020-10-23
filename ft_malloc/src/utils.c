#include "ft_malloc.h"

t_alloc_header		*get_header(void *allocation)
{
	return (allocation - sizeof(t_alloc_header));
}

t_alloc_header		*get_last_header(t_alloc_header *header)
{
	while (header->next)
		header = header->next;
	return (header);
}

int					is_tiny(void *ptr)
{
	if (ptr >= g_alloc_data.tiny && ptr < g_alloc_data.tiny + ((TINY_SIZE + sizeof(t_alloc_header)) * TINY_NB))
		return (1);
	return (0);
}

int					is_small(void *ptr)
{
	if (ptr >= g_alloc_data.small && ptr < g_alloc_data.small + ((SMALL_SIZE + sizeof(t_alloc_header)) * SMALL_NB))
		return (1);
	return (0);
}