/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:41:55 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/29 22:20:15 by ahrytsen         ###   ########.fr       */
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

static int	ft_cmd_exec_chld(t_cmd *cmd, int fg)
{
	(cmd->next || cmd->prev || !fg) ? get_environ()->pid = getpid() : 0;
	ft_redirection(cmd->toks);
	(cmd->av = ft_argv_make(cmd->toks))
		? cmd->ret = ft_argv_exec(cmd->av, NULL, fg)
		: ft_dprintf(2, "21sh: malloc error\n");
	cmd->pid = get_environ()->pid;
	ft_redirection_close(cmd->toks);
	if (cmd->next || cmd->prev || !fg)
		exit(cmd->av ? cmd->ret : 1);
	return (cmd->av ? cmd->ret : 1);
}

static int	ft_cmd_exec(t_cmd *cmd, int fg)
{
	static int	pl[2];

	if (ft_pl_make(pl, cmd))
		return (1);
	if ((cmd->next || cmd->prev || !fg) && (cmd->pid = fork()))
	{
		cmd->pid != -1
			? (get_environ()->pid = cmd->pid)
			: ft_dprintf(2, "21sh: fork() error\n");
		return (cmd->pid == -1 ? 1 : 0);
	}
	else
		return (ft_cmd_exec_chld(cmd, fg));
}

int			ft_cmdlst_exec(t_cmd *cmd, int fg)
{
	while (1)
	{
		cmd->ret = ft_cmd_exec(cmd, fg);
		ft_fildes(FD_RESTORE);
		if (cmd->ret || !cmd->next)
			break ;
		cmd = cmd->next;
	}
	return (ft_control_job(cmd, fg));
}
