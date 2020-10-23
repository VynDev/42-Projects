#include "libft.h"
#include "ft_malloc.h"
#include <unistd.h>
#include <sys/mman.h>

t_alloc_data	g_alloc_data;

int				initialize()
{
	static int	is_initialized = 0;

	if (is_initialized)
		return (1);
	g_alloc_data.large = NULL;
	if (!(g_alloc_data.tiny = allocate((TINY_SIZE + sizeof(t_alloc_header)) * TINY_NB)))
		return (0);
	init_zone(g_alloc_data.tiny, TINY_NB, TINY_SIZE);
	if (!(g_alloc_data.small = allocate((SMALL_SIZE + sizeof(t_alloc_header)) * SMALL_NB)))
		return (0);
	init_zone(g_alloc_data.small, SMALL_NB, SMALL_SIZE);
	is_initialized = 1;
	return (1);
}

void			*malloc(size_t size)
{
	void			*allocation;

	if (!initialize())
		return (NULL);
	if (size <= TINY_SIZE)
		allocation = alloc_zone(g_alloc_data.tiny, size, TINY_SIZE, TINY_NB);
	else if (size <= SMALL_SIZE)
		allocation = alloc_zone(g_alloc_data.small, size, SMALL_SIZE, SMALL_NB);
	else 
		allocation = create_large(size);
	return (allocation);
}
