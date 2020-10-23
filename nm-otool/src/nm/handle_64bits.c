#include "libft.h"
#include "nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

Elf64_Sym 		*sort_symtab(Elf64_Sym *symtab, void *strtab, int nb_elem)
{
	Elf64_Sym	*tab;
	int			i;
	int			ok;
	Elf64_Sym	tmp;

	tab = (Elf64_Sym *)malloc(sizeof(Elf64_Sym) * nb_elem);
	memcpy(tab, symtab, sizeof(Elf64_Sym) * nb_elem);
	i = 0;
	ok = 1;
	while (i < nb_elem - 1)
	{
		if (ft_strcmp_c(strtab + tab[i].st_name, strtab + tab[i + 1].st_name) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			ok = 0;
		}
		++i;
		if (ok == 0 && i == nb_elem - 1)
		{
			i = 0;
			ok = 1;
		}
	}
	return (tab);
}

char			get_symbol_type(Elf64_Sym *tab, Elf64_Shdr *sections)
{
	char			c;
	unsigned char 	info;
	Elf64_Shdr		section;

	info = tab->st_info;
	c = '?';
	if (tab->st_shndx != SHN_UNDEF)
	{
		section = sections[tab->st_shndx];
		if (section.sh_type == SHT_NOBITS)
			c = 'B';
		else if (section.sh_type == SHT_PROGBITS || section.sh_type == SHT_DYNAMIC)
		{
			c = 'D';
			if ((section.sh_flags & SHF_WRITE) == 0)
				c = 'R';
		}
		if (ELF64_ST_TYPE(info) == STT_FUNC || section.sh_type == SHT_INIT_ARRAY || section.sh_type == SHT_FINI_ARRAY)
		{
			c = 'T';
		}
	}
	else
	{
		c = 'U';
	}
	if (ELF64_ST_BIND(info) == STB_WEAK && tab->st_value)
			c = 'W';
	else if (ELF64_ST_BIND(info) == STB_WEAK)
			c = 'w';
	if (c >= 'A' && c <= 'Z' && ELF64_ST_BIND(info) == STB_LOCAL)
		c = c + 32;
	return (c);
}

void			handle_64bits_section(void *shstrtab, Elf64_Shdr *sections, Elf64_Sym *symtab, void *strtab, int nb_elem)
{
	(void)shstrtab;
	int				i;
	Elf64_Sym		*tab;

	tab = sort_symtab(symtab, strtab, nb_elem);
	i = 0;
	while (i < nb_elem)
	{
		if (ELF64_ST_TYPE(tab[i].st_info) != STT_FILE && ft_strlen(strtab + tab[i].st_name) > 0)
		{
			if (tab[i].st_shndx != SHN_UNDEF)
				ft_printf("%016x %c %s\n", tab[i].st_value, get_symbol_type(tab + i, sections), strtab + tab[i].st_name);
			else if (ft_strlen(strtab + tab[i].st_name) > 0)
				ft_printf("%16s %c %s\n", "", get_symbol_type(tab + i, sections), strtab + tab[i].st_name);
		}
		++i;
	}
}

void			handle_64bits(Elf64_Ehdr *header)
{
	Elf64_Shdr		*sections;
	int				i;
	int				nb_elem;
	Elf64_Sym		*symtab;
	char			*strtab;

	sections = (Elf64_Shdr *)((void *)header + header->e_shoff);
	i = 0;
	while (i < header->e_shnum)
	{
		if (sections[i].sh_type == SHT_SYMTAB)
		{
			symtab = (Elf64_Sym *)((void *)header + sections[i].sh_offset);
			nb_elem = sections[i].sh_size / sections[i].sh_entsize;
		}
		if (sections[i].sh_type == SHT_STRTAB)
			strtab = (void *)header + sections[i].sh_offset;
		++i;
	}
	handle_64bits_section((void *)header + sections[header->e_shstrndx].sh_offset, sections, symtab, strtab, nb_elem);
}