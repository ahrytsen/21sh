/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 20:08:03 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/22 19:51:21 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		ft_dquote_slash(t_buf **cur, char **line)
{
	if (**line == 'a')
		ft_putchar_mshbuf(cur, 7);
	else if (**line == 'b')
		ft_putchar_mshbuf(cur, 8);
	else if (**line == 't')
		ft_putchar_mshbuf(cur, 9);
	else if (**line == 'n')
		ft_putchar_mshbuf(cur, 10);
	else if (**line == 'v')
		ft_putchar_mshbuf(cur, 11);
	else if (**line == 'f')
		ft_putchar_mshbuf(cur, 12);
	else if (**line == 'r')
		ft_putchar_mshbuf(cur, 7);
	else if (**line == '0')
	{
		ft_putchar_mshbuf(cur, ft_atoi_base(*line, 8));
		while (**line >= '0' && **line < '8')
			(*line)++;
		return ;
	}
	else if (**line)
		ft_putchar_mshbuf(cur, **line);
	**line ? (*line)++ : 0;
}

void		ft_bquote_slash(t_buf **cur, char **line)
{
	if (!**line)
		return ;
	else if (**line == '`')
		ft_putchar_mshbuf(cur, **line);
	else
	{
		ft_putchar_mshbuf(cur, '\\');
		ft_putchar_mshbuf(cur, **line);
	}
	(*line)++;
}

void		ft_slash(t_buf **cur, char **line)
{
	if (!**line)
		return ;
	else
		ft_putchar_mshbuf(cur, **line);
	(*line)++;
}

static void	ft_bquote_child(int fd_get[2], char *cmds)
{
	int		i;
	char	**cmd;

	i = 0;
	msh_get_environ()->pid = 1;
	close(fd_get[0]);
	dup2(fd_get[1], 1);
	cmd = cmds ? msh_splitsemicolon(cmds) : NULL;
	while (cmd && cmd[i])
	{
		msh_get_environ()->st = ft_exec(msh_splitwhitespaces(cmd[i]), NULL);
		free(cmd[i++]);
	}
	free(cmd);
	free(cmds);
	close(fd_get[1]);
	exit(msh_get_environ()->st);
}

void		ft_bquote_helper(t_buf **cur, char *str)
{
	int		fd_get[2];
	char	*line;
	int		i;

	i = 0;
	pipe(fd_get);
	if ((msh_get_environ()->pid = fork()))
	{
		close(fd_get[1]);
		while (get_next_line(fd_get[0], &line) > 0)
		{
			i++ ? ft_putchar_mshbuf(cur, '\n') : 0;
			ft_putstr_mshbuf(cur, line, -1);
			free(line);
		}
		close(fd_get[0]);
		msh_get_environ()->pid = 0;
	}
	else
		ft_bquote_child(fd_get, str);
}
