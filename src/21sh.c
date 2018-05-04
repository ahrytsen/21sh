/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/04 14:00:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void	ft_prompt(void)
{
	char	pwd[MAXPATHLEN];

	isatty(0) ? ft_dprintf(2, "\033[33m%s \033[32m$>\033[0m ",
						getcwd(pwd, MAXPATHLEN)) : 0;
}

int		main_loop(void)
{
	char	*cmds;
	char	**cmd;
	int		i;

	while (1)
	{
		ft_prompt();
		i = !isatty(0) ? get_next_line(0, &cmds) : ft_readline(&cmds);
		if (!i || i == -1)
			return (!i ? msh_get_environ()->st : 1);
		i = 0;
		cmd = msh_splitsemicolon(cmds);
		while (cmd && cmd[i])
		{
			msh_get_environ()->st = ft_exec(msh_splitwhitespaces(cmd[i]), NULL);
			free(cmd[i++]);
		}
		free(cmd);
		free(cmds);
	}
}

int		main(void)
{
	msh_init();
	return (main_loop());
}
