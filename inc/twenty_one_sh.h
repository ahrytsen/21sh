/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 20:22:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/05 20:50:39 by ahrytsen         ###   ########.fr       */
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

/*
**	KEY BINDINGS
*/
# define K_UP 0X415B1B
# define K_AUP 0X41393B315B1B
# define K_SUP 0X41323B315B1B
# define K_DOWN 0X425B1B
# define K_ADOWN 0X42393B315B1B
# define K_SDOWN 0X42323B315B1B
# define K_LEFT 0X445B1B
# define K_ALEFT 0X621B
# define K_SLEFT 0X44323B315B1B
# define K_ASLEFT 0X4430313B315B1B
# define K_RIGHT 0X435B1B
# define K_ARIGHT 0X661B
# define K_SRIGHT 0X43323B315B1B
# define K_ASRIGHT 0X4330313B315B1B
# define K_HOME 0X485B1B
# define K_END 0X465B1B
# define K_BS 0X7F
# define K_ABS 0X7F1B
# define K_DEL 0X4
# define K_ADEL 0X641B
# define K_SPC 0X20
# define K_RET 0XA
# define K_SRCH 0X6
# define K_ESC 0X1B
# define K_TAB 0X9
# define K_CUTE 0X781B
# define K_COPY 0X631B
# define K_PASTE 0X761B
# define K_MOVE 1
# define K_WORD_MOVE 2
# define K_SELECT 3

/*
**	MODS
*/
# define T_INIT 1
# define T_RESTORE 0

/*
**	PROMPT
*/
# define P_USER 0
# define P_HEREDOC 1
# define P_DQUOTE 34
# define P_QUOTE 39
# define P_BSLASH 92
# define P_BQUOTE 96

typedef struct	s_line
{
	uint64_t		ch;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

typedef struct	s_hist
{
	t_line			*line;
	t_line			*tmp;
	struct s_hist	*next;
	struct s_hist	*prev;
}				t_hist;

typedef struct	s_term
{
	t_line	*cursor;
	t_hist	*hist;
	t_line	*st_sel;
	t_line	*end_sel;
	t_line	*buffer;
	char	*res;
	int		prompt;
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

typedef enum	e_token_type
{
	ignore,
	blank,
	word,
	pipeline,
	bg_op,
	semicolon,
	and,
	or,
	heredoc,
	heredoc_t,
	herestr,
	open_file,
	read_in,
	read_in_and,
	read_out,
	read_out_and,
	read_out_pipe,
	and_read_out,
	read_out_apend
}				t_type;

typedef union	u_data
{
	int		fd[2];
	char	*word;
}				t_data;

typedef struct	s_token
{
	t_type	type;
	t_data	data;
}				t_token;

typedef struct	s_cmd
{
	char			*av;
	t_list			*toks;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	int				ret;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

/*
**				main.c
*/
int				main_loop(void);
/*
**				init.c
*/
void			ft_init(void);
void			ft_terminal(int mod);
/*
**				ft_signal.c
*/
void			ft_init_signal(void);
/*
**				ft_tokenizer.c
*/
t_list			*ft_tokenizer(char *ln);
/*
**				ft_tokenizer_helper.c
*/
int				ft_isseparator(int c);
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
char			**msh_splitsemicolon(char *line);
char			**msh_splitwhitespaces(char *line);
void			ft_slash(t_buf **cur, char **line);
void			ft_bquote(t_buf **cur, char **line, uint8_t q);
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
int				ft_readline(const int fd, char **line);
/*
**				ft_readline/ft_readline_action.c
*/
void			ft_back_space(void);
void			ft_move(uint64_t buf);
int				ft_add(uint64_t buf);
int				ft_del(void);
void			ft_word_action(uint64_t buf);
/*
**				ft_readline/ft_readline_helper.c
*/
int				term_print(int c);
t_term			*get_term(void);
void			ft_readline_ret(void);
void			ft_print_tail(t_line *cursor);
void			ft_redraw_line(void);

/*
**				ft_readline/ft_cursor.c
*/
void			ft_curleft(int mod);
void			ft_curright(int mod);
void			ft_curnleft(int mod, int n);
void			ft_curnright(int mod, int n);
void			ft_curhome(void);
/*
**				ft_readline/line.c
*/
t_line			*copy_line(t_line *line);
char			*line_tostr(t_line **cursor, int mod);
int				line_bs(t_line *cursor);
int				line_add(t_line *cursor, uint64_t ch);
/*
**				ft_readline/line_edit.c
*/
void			line_cute(void);
int				line_copy(void);
void			line_paste(void);
int				ft_copy_paste(uint64_t buf);
/*
**				ft_readline/ft_autocomplit.c
*/
void			ft_autocomplit(t_line *cursor);
/*
**				ft_readline/ft_history.c
*/
int				hist_init(void);
void			hist_move(uint64_t buf);
void			clean_hist(void);
void			hist_commit(int st);
/*
**				ft_readline/ft_highlight.c
*/
void			ft_highlight(uint64_t buf);
uint64_t		ft_highlight_helper(uint64_t buf);
/*
**				ft_readline/ft_prompt.c
*/
void			ft_prompt(void);
/*
**				ft_readline/ft_check_line.c
*/
int				ft_check_line(char *ln);

#endif
