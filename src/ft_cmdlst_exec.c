/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 20:04:56 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/14 20:41:41 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_count_args(t_list *toks)
{
	int	ret;

	ret = 0;
	while (toks)
	{
		if (((t_token*)(toks->content))->type == word)
			ret++;
		toks = toks->next;
	}
	return (ret);
}

char	**ft_make_av(t_list *toks)
{
	int		i;
	int		size;
	char	**av;

	i = 0;
	size = ft_count_args(toks) + 1;
	if (!(av = ft_memalloc(size * sizeof(av))))
		return (NULL);
	while (i < size && toks)
	{
		if (((t_token*)(toks->content))->type == word
			&& !(av[i++] = parse_argv(((t_token*)(toks->content))->data.word)))
		{
			ft_strarr_free(av);
			return (NULL);
		}
		toks = toks->next;
	}
	return (av);
}

void		ft_cmdexec(t_cmd *cmd)
{
	static int	fd[2];
	static int	bkp_fd[3];

	bkp_fd[0] = dup(0);
	bkp_fd[1] = dup(1);
	bkp_fd[2] = dup(2);
	if (cmd->prev)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (cmd->next)
	{
		pipe(fd);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (cmd->next || cmd->prev)
	{
		if ((cmd->pid = fork()))
		{
			get_environ()->pid = cmd->pid;
			if (!cmd->next)
			{
				waitpid(cmd->pid, &cmd->ret, 0);
				get_environ()->pid = 0;
			}
		}
		else
		{
			get_environ()->pid = 1;
			if ((cmd->av = ft_make_av(cmd->toks)))
				cmd->ret = ft_exec(cmd->av, NULL);
			exit(cmd->ret);
		}
	}
	else
	{
		if ((cmd->av = ft_make_av(cmd->toks)))
			cmd->ret = ft_exec(cmd->av, NULL);
	}
	dup2(bkp_fd[0], 0);
	dup2(bkp_fd[1], 1);
	dup2(bkp_fd[2], 2);
}

int		ft_cmdlst_exec(t_ast *ast)
{
	t_cmd	*cmd;

	cmd = ast->cmd;
	while (1)
	{
		ft_cmdexec(cmd);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	cmd = ast->cmd;
	while (1)
	{
		cmd->pid > 0 ? kill(cmd->pid, SIGKILL) : 0;
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	return (cmd->ret);
}
