#include "libft.h"
#include "nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		ft_strcmp_c(const char *ss1, const char *ss2)
{
	const char *s1;
	const char *s2;

	s1 = ss1;
	s2 = ss2;
	while (*(unsigned char *)s1 && *s1 == '_')
		++s1;
	while (*(unsigned char *)s2 && *s2 == '_')
		++s2;
	while (ft_tolower(*(unsigned char *)s1) == ft_tolower(*(unsigned char *)s2))
	{
		if (*s1 == '\0')
			return (ft_strcmp(ss1, ss2));
		s1++;
		s2++;
		while (*(unsigned char *)s1 && *s1 == '_')
			++s1;
		while (*(unsigned char *)s2 && *s2 == '_')
			++s2;
	}
	return (ft_tolower(*(unsigned char *)s1) - ft_tolower(*(unsigned char *)s2));
}
