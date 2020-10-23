/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:25:05 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 15:59:23 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# include <termcap.h>
//# include <curses.h> // -lcurses
# include <signal.h>

# define ABS(x) ((x < 0) ? -(x) : x)
# define BUFFER_SIZE_CMD 256

typedef struct	s_tab_builtin
{
	char		*command;
	void		(*f)(int, char **);

}				t_tab_builtin;

typedef struct	s_data
{
	int			exit_shell;
	char		**env;
	char		*last_dir;
	pid_t		fork_pid;
	struct termios	termios_backup;

}				t_data;

typedef struct	s_command
{
	char		*line;
	int			cursor;
	int			buffer_size;
}				t_command;

void			print_env(char **env);
void			print_arg(int ac, char **av);
void			print_error(char *str, char *command);

t_data			*get_data();
void			data_init();
void			data_free();


char			*ft_env_getvalue(char **env, char *key);
int				ft_env_setvalue(char ***env_root, char *key, char *value);
int				ft_env_delvalue(char ***env_root, char *key);

char			**ft_tabdup(char **tab);
char			**ft_tabadd(char **tab, char *str);


int				file_check_access(char *file);
int				file_check(char *file, char *command);

char			*get_right_path(char *filename, char **env);

t_tab_builtin	*get_tab_builtin();

void			builtin_exit(int ac, char **av);
void			builtin_cd(int ac, char **av);
void			builtin_setenv(int ac, char **av);
void			builtin_env(int ac, char **av);
void			builtin_unsetenv(int ac, char **av);
void			builtin_echo(int ac, char **av);

char			**split_wsquote(char const *s);
char			**ft_strsplit_quote(char const *s, char c);

int				get_input(int fd, char **line);

void			term_init();
void			term_reset();

void			get_commands(char *line, t_data	*data);
int				do_builtin(char **command);

#endif
