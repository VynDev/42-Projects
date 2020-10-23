#include "libft.h"
#include "nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void			ft_strtoupper(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		++str;
	}
}

void			handle_64bits_section(Elf64_Ehdr *header, void *section, Elf64_Xword sh_size)
{
	Elf64_Xword			i;
	char				*str;
	char				*tmp;

	i = 0;
	ft_printf("size: %lu\n", sh_size);
	while (i < sh_size)
	{
		if (i % 16 == 0)
		{
			tmp = ft_jitoa_base(((unsigned long int)(section + i) - (unsigned long int)header) + 0x400000, 16);
			ft_printf("%s\t\t", tmp);
			free(tmp);
		}
		str = ft_ctoa_base(*((char *)section + i), 16);
		if (ft_strlen(str) == 1)
			ft_putchar('0');
		ft_printf("%s%c", str, ((i + 1) % 16 == 0) ? '\n' : ' ');;
		i = i + 1;
	}
	ft_putchar('\n');
}

void			handle_64bits(Elf64_Ehdr *header)
{
	Elf64_Shdr		*sections;
	int				i;

	sections = (Elf64_Shdr *)((void *)header + header->e_shoff);
	i = 0;
	while (i < header->e_shnum)
	{
		if (ft_strcmp((void *)header + sections[header->e_shstrndx].sh_offset + sections[i].sh_name, ".text") == 0)
			handle_64bits_section(header, (void *)header + sections[i].sh_offset, sections[i].sh_size);
		++i;
	}
}

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

void			ft_putnstr_c(char *str, int n)
{
	while (n != 0 && *str != '/')
	{
		ft_putchar(*str);
		--n;
		++str;
	}
	ft_putstr(":\n");
}

void			ft_putnstr_c2(char *str)
{
	while (*str != '/')
	{
		ft_putchar(*str);
		++str;
	}
	ft_putstr(":\n");
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