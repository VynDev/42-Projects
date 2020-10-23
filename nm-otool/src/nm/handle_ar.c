#include "libft.h"
#include "nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void			*get_extended_filename_section(void *ptr, struct stat buf)
{
	struct ar_hdr	*header;

	header = ptr + SARMAG;
	while ((void *)header - ptr < buf.st_size)
	{
		if (header->ar_name[0] == '/' && header->ar_name[1] == '/')
			return ((void *)header + sizeof(struct ar_hdr));
		header = (void *)header + sizeof(struct ar_hdr) + ft_atoi(header->ar_size);
	}
	return (NULL);
}

void			handle_ar(void *ptr, struct stat buf)
{
	struct ar_hdr	*header;
	void			*extended_filename_section;
	int				i;

	
	extended_filename_section = get_extended_filename_section(ptr, buf);
	header = ptr + SARMAG;
	i = 0;
	while ((void *)header - ptr < buf.st_size && i < 2)
	{
		header = (void *)header + sizeof(struct ar_hdr) + ft_atoi(header->ar_size);
		++i;
	}
	while ((void *)header - ptr < buf.st_size)
	{
		//ft_printf("%s\n", header->ar_size);
		ft_putchar('\n');
		if (header->ar_name[0] == '/' && ft_isdigit(header->ar_name[1]))
			ft_putnstr_c2(extended_filename_section + ft_atoi(header->ar_name + 1));
		else
			ft_putnstr_c(header->ar_name, 16);
		handle_elf((void *)header + sizeof(struct ar_hdr));
		header = (void *)header + sizeof(struct ar_hdr) + ft_atoi(header->ar_size);
	}
}