/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 20:22:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/11 20:22:43 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_SH_H
# define TWENTY_ONE_SH_H

# include <libft.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>

typedef struct	s_line
{
	uint64_t		ch;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

typedef struct	s_term
{
	t_line	*cursor;
	int		curx;
	int		cury;
	char	*clear;
	char	*curmov;
	char	*cm_left;
	char	*cm_right;
	char	*undln_on;
	char	*undln_off;
	char	*iv_on;
	char	*iv_off;
	char	*im_on;
	char	*im_off;
	char	*del_ch;
	char	*dm_on;
	char	*dm_off;
	int		height;
	int		width;
}				t_term;

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

typedef struct	s_env
{
	char		**env;
	int			st;
	pid_t		pid;
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
**				builtins/builtins.c
*/
int				ft_echo(char **av);
int				ft_setenv_builtin(char **av);
int				ft_unsetenv_builtin(char **av);
int				ft_exit(char **av);
/*
**				builtins/ft_cd.c
*/
int				ft_cd(char **av);
/*
**				builtins/env_builtin.c
*/
int				ft_env(char **av);
/*
**				msh
*/
int				ft_exec(char **cmd, char *altpath);
t_env			*get_environ(void);
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
**				buffer
*/
t_buf			*ft_new_mshbuf(void);
void			ft_putstr_mshbuf(t_buf **buf, char *str, ssize_t len);
void			ft_putchar_mshbuf(t_buf **buf, char c);
char			*ft_buftostr(t_buf *buf_head);
void			*ft_free_mshbuf(t_buf *buf);
/*
**				ft_readline/ft_readline.c
*/
int				term_print(int c);
t_term			*get_term(void);
int				ft_readline(const int fd, char **line);
/*
**				ft_readline/ft_readline_action.c
*/
void			ft_back_space(void);
void			ft_move(uint64_t buf);
void			ft_add(uint64_t buf);
/*
**				ft_readline/ft_cursor.cx
*/
void			ft_print_tail(t_line *cursor);
void			ft_curleft(int mod);
void			ft_curright(int mod);
void			ft_curnleft(int mod, int n);
/*
**				ft_readline/line.c
*/
char			*line_tostr(t_line **cursor, int mod);
int				line_bs(t_line *cursor);
int				line_add(t_line *cursor, uint64_t ch);
/*
**				ft_readline/ft_autocomplit.c
*/
void			ft_autocomplit(t_line *cursor);

#endif