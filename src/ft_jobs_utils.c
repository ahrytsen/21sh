/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:37:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/29 22:51:42 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	ft_stop_job(void)
{
	t_list	*proc;

	if (get_environ()->pid > 1 && (proc = ft_memalloc(sizeof(t_list))))
	{
		proc->content_size = get_environ()->pid;
		ft_lstadd(&get_environ()->jobs, proc);
	}
}

int		ft_control_job_fg(void)
{
	int	ret;

	ret = 0;
	if (get_environ()->pid)
	{
		setpgid(get_environ()->pid, get_environ()->pid);
		tcsetpgrp(1, get_environ()->pid);
		waitpid(get_environ()->pid, &ret, WUNTRACED);
		tcsetpgrp(1, get_environ()->sh_pid);
		WIFSTOPPED(ret) ? ft_stop_job() : 0;
		get_environ()->pid = 0;
	}
	return (ret);
}

int		ft_control_job(t_cmd *cmd, int fg)
{
	int	ret;

	if (!cmd->ret && cmd->pid)
	{
		setpgid(cmd->pid, cmd->pid);
		tcsetpgrp(1, cmd->pid);
		fg ? waitpid(cmd->pid, &cmd->ret, WUNTRACED) : ft_stop_job();
		tcsetpgrp(1, get_environ()->sh_pid);
		WIFSTOPPED(cmd->ret) ? ft_stop_job() : 0;
		get_environ()->pid = 0;
	}
	ret = cmd->ret;
	while (!WIFSTOPPED(ret) && fg && (cmd = cmd->prev))
		if (cmd->pid > 0 && !kill(cmd->pid, SIGKILL))
		{
			waitpid(cmd->pid, &cmd->ret, WUNTRACED);
			cmd->ret = WEXITSTATUS(cmd->ret);
		}
	return (ret);
}

int		ft_status_job(int st)
{
	if (WIFSTOPPED(st))
		st = -WEXITSTATUS(st);
	else
		st = WIFSIGNALED(st) ? -WTERMSIG(st) : WEXITSTATUS(st);
	return (st);
}
