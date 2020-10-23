#include "ft_malloc.h"
#include "libft.h"

void			*find_free_memory(void *zone, int max_size, int nb)
{
	int				i;
	t_alloc_header	*header;

	i = 0;
	header = (t_alloc_header *)zone;
	while (i < nb)
	{
		if (header->size == 0)
			return (header);
		if (!header->next && i + 1 < nb)
		{
			header->next = (void *)header + max_size + sizeof(t_alloc_header);
			((t_alloc_header *)header->next)->size = 0;
			((t_alloc_header *)header->next)->next = NULL;
			((t_alloc_header *)header->next)->previous = header;
		}
		header = header->next;
		++i;
	}
	return (NULL);
}

void			*alloc_zone(void *zone, size_t size, int max_size, int nb)
{
	void			*allocation;
	t_alloc_header	*header;

	allocation = find_free_memory(zone, max_size, nb);
	if (allocation)
	{
		header = (t_alloc_header *)allocation;
		header->size = size;
	}
	else
		return(create_large(size));
	return (allocation + sizeof(t_alloc_header));
}