#include "libft.h"
#include "nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void			handle_elf(void *ptr)
{
	if (*(char *)(ptr + EI_CLASS) == ELFCLASS32)
	{
		ft_printf("It's a 32-bits object (Not supported yet)\n");
	}
	else if (*(char *)(ptr + EI_CLASS) == ELFCLASS64)
	{
		//ft_printf("It's a 64-bits object\n");
		handle_64bits(ptr);
	}
}