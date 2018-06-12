/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:53:42 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/12 21:21:31 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_get_pipe(t_list **toks, t_cmd *cmdlst)
{
	if ()
}

static void	ft_get_cmd(t_list **toks, t_cmd *cmd)
{
	t_list	*tmp;

	cmd->toks = *toks;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->fd_err = 2;
	while (*toks && ((t_token*)toks->content)->type != pipeline)
	{
		tmp = *toks;
		*toks = (*toks)->next;
	}
	tmp->next = NULL;
}

t_cmd	*ft_make_cmdlst(t_list **toks)
{
	t_cmd	*cmdlst;
	t_cmd	*tmp;
	t_cmd	cmd;

	cmdlst = NULL;
	while (toks)
	{
		ft_bzero(&cmd, sizeof(cmd));
		if (((t_token*)toks->content)->type == pipeline
			&& ft_get_pipe(&toks, cmdlst))
			return (ft_cmdlst_del(cmdlst));
		ft_get_cmd(&toks, &cmd);
	}
	return (NULL);
}
