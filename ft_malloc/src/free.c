#include "ft_malloc.h"
#include "libft.h"

int				is_allocated(void *ptr)
{
	t_alloc_header	*zone_header;
	t_alloc_header	*header;

	header = get_header(ptr);
	if (is_tiny(header))
		zone_header = g_alloc_data.tiny;
	else if (is_small(header))
		zone_header = g_alloc_data.small;
	else
		zone_header = g_alloc_data.large;
	while (zone_header)
	{
		if (header == zone_header)
		{
			if (zone_header->size == 0)
				return (0);
			return (1);
		}
		zone_header = zone_header->next;
	}
	return (0);
}

int				real_free(void *ptr)
{
	t_alloc_header	*header;

	if (!ptr)
		return (0);
	if (!is_allocated(ptr))
		return (0);
	header = get_header(ptr);
	if (is_tiny(header))
		free_zone(header);
	else if (is_small(header))
		free_zone(header);
	else
		free_large(header);
	return (1);
}

void			free(void *ptr)
{
	real_free(ptr);
}