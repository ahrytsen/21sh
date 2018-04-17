/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/22 20:01:46 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_prompt(void)
{
	char	pwd[MAXPATHLEN];

	isatty(0) ? ft_dprintf(2, "\033[33m%s \033[32m$>\033[0m ",
						getcwd(pwd, MAXPATHLEN)) : 0;
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		cmdline_free(msh_get_environ()->cursor);
		if (isatty(0) && !msh_get_environ()->pid)
		{
			ft_dprintf(2, "\n");
			ft_prompt();
		}
	}
	return ;
}

void	msh_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	msh_get_environ()->env = ft_strdup_arr(environ);
	msh_get_environ()->cursor = ft_memalloc(sizeof(t_cmdline));
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	ft_setenv("PATH", "/usr/bin:/bin", 0);
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGINFO, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
