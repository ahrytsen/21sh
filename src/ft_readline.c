/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/22 20:14:22 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**#ifdef unix
**static char term_buffer[2048];
**#else
**#define term_buffer 0
**#endif
**
**void	init_terminal_data()
**{
**  char	*termtype = getenv ("TERM");
**  int 	success;
**
**  if (termtype == 0)
**	  ft_dprintf(2, "Specify a terminal type with `setenv TERM <yourtype>'.\n");
**  success = tgetent (term_buffer, termtype);
**  if (success < 0)
**    ft_dprintf(2, "Could not access the termcap data base.\n");
**  if (success == 0)
**    ft_dprintf(2, "Terminal type `%s' is not defined.\n", termtype);
**}
**
**
**static char	*ft_search_files(char	*line)
**{
**	DIR				*dirp;
**	struct dirent	*dp;
**	int				len;
**	char			*path;
**
**	if (!line || (path = NULL))
**		return (NULL);
**	if (ft_strchr(line, '/'))
**	{
**		path = ft_strsub(line, 0, ft_strrchr(line, '/') - line + 1);
**		line = ft_strrchr(line, '/') + 1;
**	}
**	if (*path != '/' && ft_strncmp(path, "./", 2))
**		path = ft_strextend(ft_strdup("./"), path);
**	len = ft_strlen(line);
**	dirp = opendir(path);
**	while (dirp && (dp = readdir(dirp)))
**		if (!ft_strncmp(dp->d_name, line, len) && !closedir(dirp))
**		{
**			free(path);
**			return (ft_strdup(dp->d_name));
**		}
**	closedir(dirp);
**	free(path);
**	return (NULL);
**}
*/

static char	*ft_search_builtin(char *line)
{
	int					i;
	int					len;
	const static char	*builtins[] = {"echo", "cd", "setenv", "unsetenv",
									"env", "exit", NULL};

	i = 0;
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (builtins[i] && ft_strncmp(line, builtins[i], len))
		i++;
	return (builtins[i] ? ft_strdup(builtins[i]) : NULL);
}

static char	*ft_searchcmd(char *line)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				len;
	int				i;
	char			**path;

	if (!line || !(path = ft_strsplit(ft_getenv("PATH"), ':')))
		return (NULL);
	i = 0;
	len = ft_strlen(line);
	while (path[i])
	{
		dirp = opendir(path[i++]);
		while (dirp && (dp = readdir(dirp)))
			if (ft_strncmp(dp->d_name, line, len) == 0)
			{
				closedir(dirp);
				ft_strarr_free(path);
				return (ft_strdup(dp->d_name));
			}
		closedir(dirp);
	}
	ft_strarr_free(path);
	return (NULL);
}

void		ft_autocomplit(t_cmdline *cursor)
{
	char	*line;
	char	*res;
	char	*tmp;

	line = cmdline_tostr(cursor, 0);
	res = ft_search_builtin(line);
	(!res) ? res = ft_searchcmd(line) : 0;
	if (res)
	{
		tmp = res + ft_strlen(line);
		while (*tmp && ft_printf("%c", *tmp))
			cmdline_addch(cursor, *tmp++);
		ft_printf(" ");
		cmdline_addch(cursor, ' ');
	}
	else
		ft_printf("\a");
	free(res);
	free(line);
}

int			ft_readline(char **line)
{
	struct termios	savetty;
	struct termios	tty;
	uint64_t		buf;

	tcgetattr(0, &tty);
	savetty = tty;
	tty.c_lflag &= ~(ICANON | ECHO);
	tty.c_cc[VMIN] = 1;
	tcsetattr(0, TCSAFLUSH, &tty);
	while (!(buf = 0) && read(0, &buf, 8) > 0 && buf != 4)
		if (buf == '\n' && ft_dprintf(0, "\n"))
			break ;
		else if (buf == '\t')
			ft_autocomplit(msh_get_environ()->cursor);
		else if (buf == 127 && !cmdline_bs(msh_get_environ()->cursor))
			ft_dprintf(0, "%c\033[0J", 8);
		else if (buf == 0X445B1B || buf == 0X435B1B
				|| buf == 0X415B1B || buf == 0X425B1B)
			ft_dprintf(0, "\a");
		else if (buf != 127 && ft_dprintf(0, "%s", &buf)
				&& (buf > 31 || ft_iswhitespace(buf)))
			cmdline_add(msh_get_environ()->cursor, buf);
	tcsetattr(0, TCSANOW, &savetty);
	*line = cmdline_tostr(msh_get_environ()->cursor, 1);
	return (buf == '\n' ? 1 : 0);
}
