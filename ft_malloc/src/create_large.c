#include "ft_malloc.h"

void			*create_large(size_t size)
{
	void			*allocation;
	t_alloc_header	*header;
	t_alloc_header	*last_header;

	if (!(allocation = allocate(size + sizeof(t_alloc_header))))
		return (NULL);
	header = (t_alloc_header *)allocation;
	header->size = size;
	if (!g_alloc_data.large)
	{
		header->previous = NULL;
		header->next = NULL;
		g_alloc_data.large = allocation;
	}
	else
	{
		last_header = get_last_header(g_alloc_data.large);
		header->previous = last_header;
		header->next = NULL;
		last_header->next = header;
	}
	return (allocation + sizeof(t_alloc_header));
}