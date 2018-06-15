/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 20:04:56 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/15 18:39:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_pl_make(int pl[2], t_cmd *cmd)
{
	if (cmd->prev)
	{
		dup2(pl[0], 0);
		close(pl[0]);
	}
	if (cmd->next)
	{
		if (pipe(pl) && ft_dprintf(2, "21sh: pipe error\n"))
			return (1);
		dup2(pl[1], 1);
		close(pl[1]);
	}
	return (0);
}

static int	ft_pl_exec(t_cmd *cmd)
{
	static int	pl[2];

	if (ft_pl_make(pl, cmd))
		return (1);
	if ((cmd->pid = fork()))
	{
		cmd->pid != -1 ? (get_environ()->pid = cmd->pid) : 0;
		ft_fildes(FD_RESTORE);
		return (cmd->pid == -1 ? 1 : 0);
	}
	else
	{
		get_environ()->pid = 1;
		(cmd->av = ft_argv_make(cmd->toks))
			? cmd->ret = ft_argv_exec(cmd->av, NULL)
			: ft_dprintf(2, "21sh: malloc error\n");
		exit(cmd->av ? cmd->ret : 1);
	}
	return (0);
}

static int	ft_cmd_exec(t_cmd *cmd)
{
	if (cmd->next || cmd->prev)
		return (ft_pl_exec(cmd));
	else
	{
		(cmd->av = ft_argv_make(cmd->toks))
			? cmd->ret = ft_argv_exec(cmd->av, NULL)
			: ft_dprintf(2, "21sh: malloc error\n");
		ft_fildes(FD_RESTORE);
		cmd->av ? 0 : (cmd->ret = -1);
		return (cmd->av ? 0 : 1);
	}
}

int		ft_cmdlst_exec(t_cmd *cmd)
{
	int	ret;

	while (!ft_cmd_exec(cmd))
	{
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	waitpid(get_environ()->pid, &cmd->ret, 0);
	cmd->ret = WEXITSTATUS(cmd->ret);
	get_environ()->pid = 0;
	ret = cmd->ret;
	while (cmd->prev)
		cmd->pid > 0 ? kill(cmd->pid, SIGKILL) : 0;
	return (ret);
}
