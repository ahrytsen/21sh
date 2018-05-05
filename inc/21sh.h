/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:57:34 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/05 18:45:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <libft.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>

# define ENV_PRINT 0
# define ENV_CLEAR 1

typedef struct	s_op
{
	int		v;
	int		i;
	char	*ap;
	char	*p;
	char	**exec;
}				t_op;

typedef struct	s_cmdline
{
	char				ch;
	struct s_cmdline	*next;
	struct s_cmdline	*prev;
}				t_cmdline;

typedef struct	s_env
{
	char		**env;
	int			st;
	t_cmdline	*cursor;
	pid_t		pid;
	char		*clear;
	char		*curmov;
	char		*cm_left;
	char		*cm_right;
	char		*undln_on;
	char		*undln_off;
	char		*iv_on;
	char		*iv_off;
	char		*im_on;
	char		*im_off;
	char		*del_ch;
	char		*dm_on;
	char		*dm_off;
	int			height;
	int			width;
}				t_env;

typedef struct	s_builtins
{
	char	*cmd;
	int		(*ft_builtin)();
}				t_builtins;

typedef struct	s_buf
{
	size_t			id;
	size_t			len;
	char			str[BUFF_SIZE];
	struct s_buf	*next;
}				t_buf;

/*
**typedef struct	s_cmd
**{
**	char			*av;
**	int				fd_in;
**	int				fd_out;
**	struct s_cmd	*next;
**	struct s_cmd	*prev;
**}				t_cmd;
*/

/*
**				21sh.c
*/
void			ft_prompt(void);
int				main_loop(void);
/*
**				init.c
*/
void			ft_init(void);
void			ft_init_terminal(int mod);
/*
**				ft_autocomplit.c
*/
void			ft_autocomplit(t_cmdline *cursor);

/*
**				Builtins
*/
int				ft_echo(char **av);
int				ft_cd(char **av);
int				ft_env(char **av);
int				ft_setenv_builtin(char **av);
int				ft_unsetenv_builtin(char **av);
int				ft_exit(char **av);
/*
**				msh
*/
int				ft_exec(char **cmd, char *altpath);
t_env			*msh_get_environ(void);
void			ft_env_op(int p);
char			*ft_getenv(const char *name);
int				ft_setenv(const char *name, const char *value, int overwrite);
int				ft_unsetenv(const char *name);
char			*parse_argv(char *line);
char			*parse_line(char *line);
char			**msh_splitsemicolon(char *line);
char			**msh_splitwhitespaces(char *line);
void			ft_slash(t_buf **cur, char **line);
void			ft_bquote(t_buf **cur, char **line);
void			ft_bquote_slash(t_buf **cur, char **line);
void			ft_dquote_slash(t_buf **cur, char **line);
void			ft_bquote_helper(t_buf **cur, char *str);
/*
**				error
*/
void			malloc_fail(void);
void			quotes_error(char q);
void			syntax_error(void);
/*
**				buffer
*/
t_buf			*ft_new_mshbuf(void);
void			ft_putstr_mshbuf(t_buf **buf, char *str, ssize_t len);
void			ft_putchar_mshbuf(t_buf **buf, char c);
char			*ft_buftostr(t_buf *buf_head);
void			*ft_free_mshbuf(t_buf *buf);
/*
**				cmdline
*/
int				ft_readline(char **line);
char			*cmdline_tostr(t_cmdline *cmdline, int mod);
int				cmdline_bs(t_cmdline *cmdline);
int				cmdline_add(t_cmdline *cmdline, uint64_t buf);
int				cmdline_addch(t_cmdline *cmdline, char ch);
void			cmdline_free(t_cmdline *cmdline);

#endif
