/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 20:04:56 by ahrytsen          #+#    #+#             */

/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_pl_make(int pl[2], t_cmd *cmd)
{
	if (cmd->prev)
	{
		dup2(pl[0], 0);
		close(pl[0]);
		close(pl[1]);
	}
	if (cmd->next)
	{
		if (pipe(pl) && ft_dprintf(2, "21sh: pipe error\n"))
			return (1);
		dup2(pl[1], 1);
	}
	return (0);
}

static int	ft_cmd_exec(t_cmd *cmd)
{
	static int	pl[2];

	if (ft_pl_make(pl, cmd))
		return (1);
	if ((cmd->next || cmd->prev) && (cmd->pid = fork()))
	{
		cmd->pid != -1
			? (get_environ()->pid = cmd->pid)
			: ft_dprintf(2, "21sh: fork error\n");
		return (cmd->pid == -1 ? 1 : 0);
	}
	else
	{
		(cmd->next || cmd->prev) ? get_environ()->pid = 1 : 0;
		ft_redirection(cmd->toks);
		(cmd->av = ft_argv_make(cmd->toks))
			? cmd->ret = ft_argv_exec(cmd->av, NULL)
			: ft_dprintf(2, "21sh: malloc error\n");
		ft_redirection_close(cmd->toks);
		if (cmd->next || cmd->prev)
			exit(cmd->av ? cmd->ret : 1);
		return (cmd->av ? cmd->ret : 1);
	}
}

int			ft_cmdlst_exec(t_cmd *cmd)
{
	int	ret;

	while (1)
	{
		cmd->ret = ft_cmd_exec(cmd);
		ft_fildes(FD_RESTORE);
		if (cmd->ret || !cmd->next)
			break ;
		cmd = cmd->next;
	}
	if (!cmd->ret && get_environ()->pid)
	{
		waitpid(get_environ()->pid, &cmd->ret, WUNTRACED);
		cmd->ret = WEXITSTATUS(cmd->ret);
	}
	ret = cmd->ret;
	get_environ()->pid = 0;
	while ((cmd = cmd->prev))
		cmd->pid > 0 && !kill(cmd->pid, SIGKILL)
			? waitpid(cmd->pid, &cmd->ret, WUNTRACED) : 0;
	return (ret);
}
