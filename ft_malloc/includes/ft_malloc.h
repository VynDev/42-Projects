/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:48:24 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:37:40 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h>
# include <inttypes.h>

# define TINY_SIZE 1024
# define TINY_NB 1024
# define TINY_LENGTH TINY_SIZE * TINY_MAX
# define SMALL_SIZE 4096
# define SMALL_NB 1024
# define SMALL_LENGTH SMALL_SIZE * SMALL_MAX

typedef struct			s_alloc_header
{
	size_t				size;
	void				*next;
	void				*previous;
}						t_alloc_header;

typedef struct			s_alloc_data
{
	void				*tiny;
	void				*small;
	void				*large;
}						t_alloc_data;

extern	t_alloc_data	g_alloc_data;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem();

void					*alloc_zone(void *zone, size_t size, int size_max, int nb);
void					*create_large(size_t size);
void					init_zone(void *zone, int nb, int size);

void					free_large(t_alloc_header *header);
void					free_zone(t_alloc_header *header);

int						is_tiny(void *ptr);
int						is_small(void *ptr);
int						is_allocated(void *ptr);

void					*allocate(size_t size);
t_alloc_header			*get_header(void *allocation);
t_alloc_header			*get_last_header(t_alloc_header *header);

void					ft_putbase(uintmax_t value, unsigned int base);

#endif
