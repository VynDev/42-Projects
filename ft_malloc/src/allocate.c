#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

size_t			get_next_multiple(size_t size)
{
	size_t		page_size;
	size_t		i;

	i = 1;
	page_size = getpagesize();
	while (page_size * i < size)
		++i;
	return (page_size * i);
}

void			*allocate(size_t size)
{
	char		*alloc;

	alloc = (char *)mmap(NULL, get_next_multiple(size), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	return (alloc == MAP_FAILED ? NULL : alloc);
}