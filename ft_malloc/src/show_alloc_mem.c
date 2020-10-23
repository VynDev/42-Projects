#include "ft_malloc.h"
#include "libft.h"

unsigned int			print_mem(t_alloc_header *header)
{
	unsigned int		count;

	count = 0;
	while (header)
	{	
		if (header->size)
		{
			ft_putstr("0x");
			ft_putbase((uintmax_t)header + sizeof(t_alloc_header), 16);
			ft_putstr(" - 0x");
			ft_putbase((uintmax_t)header + sizeof(t_alloc_header) + header->size, 16);
			ft_putstr(" : ");
			ft_putbase(header->size, 10);
			ft_putstr(" octets");
			ft_putchar('\n');
			count += header->size;
		}
		header = header->next;
	}
	return (count);
}

void					show_alloc_mem()
{
	t_alloc_header		*header;
	uintmax_t			total;

	total = 0; 
	header = g_alloc_data.tiny;
	if (header)
	{
		ft_putstr("TINY : 0x");
		ft_putbase((uintmax_t)(g_alloc_data.tiny), 16);
		ft_putchar('\n');
		total = print_mem(header);
	}
	header = g_alloc_data.small;
	if (header)
	{
		ft_putstr("SMALL : 0x");
		ft_putbase((uintmax_t)(g_alloc_data.small), 16);
		ft_putchar('\n');
		total += print_mem(header);
	}
	header = g_alloc_data.large;
	if (header)
	{
		ft_putstr("LARGE : 0x");
		ft_putbase((uintmax_t)(g_alloc_data.large), 16);
		ft_putchar('\n');
		total += print_mem(header);
	}
	ft_putstr("Total : ");
	ft_putbase(total, 10);
	ft_putstr(" octets\n");
}
