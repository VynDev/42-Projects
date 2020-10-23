#include "libft.h"
#include "ft_malloc.h"

void			*realloc(void *ptr, size_t size)
{
	void			*new_allocation;
	size_t			size_ref;
	t_alloc_header	*header;

	if (!ptr)
		return (malloc(size));
	if (!is_allocated(ptr))
		return (NULL);
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	header = get_header(ptr);
	if (size < header->size)
		size_ref = size;
	else
		size_ref = header->size;
	new_allocation = malloc(size);
	ft_memcpy(new_allocation, ptr, size_ref);
	free(ptr);
	return (new_allocation);
}

void			*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (NULL);
	ptr = malloc(nmemb * size);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}