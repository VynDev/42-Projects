#include "libft.h"
#include "nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int				main(int argc, char **argv)
{
	int				fd;
	void			*ptr;
	struct stat		buf;
	char			*mag;

	if (argc != 2)
	{
		ft_printf("I need an argument\n");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("Can't open this file\n");
		return (0);
	}
	fstat(fd, &buf);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("Error when using mmap\n");
		return (0);
	}
	close (fd);
	//ft_printf("File mapping success!\n");
	mag = (char *)ptr;
	if (mag[EI_MAG0] == ELFMAG0 && mag[EI_MAG1] == ELFMAG1 && mag[EI_MAG2] == ELFMAG2 && mag[EI_MAG3] == ELFMAG3)
	{
		//ft_printf("ELF file detected\n");
		handle_elf(ptr);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
	{
		//ft_printf("Ar file detected\n");
		handle_ar(ptr, buf);
	}
	else
	{
		//ft_printf("This is not an ELF file\n");
	}
	return (0);
}