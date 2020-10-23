#include "libft.h"
#include "ft_malloc.h"
#include <sys/mman.h>

void	free_large(t_alloc_header *header)
{
	void			*allocation;
	size_t			size;

	size = header->size;
	if (header->previous)
		((t_alloc_header *)header->previous)->next = header->next;
	if (header->next)
		((t_alloc_header *)header->next)->previous = header->previous;
	if (g_alloc_data.large == header)
		g_alloc_data.large = NULL;
	allocation = (void *)header;
	munmap(allocation, size + sizeof(t_alloc_header));
}