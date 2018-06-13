/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:53:42 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/13 17:35:22 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_get_pipe(t_list **toks, t_cmd *cmdlst)
{
	t_list	*tmp;

	tmp = *toks;
	*toks = (*toks)->next;
	tmp->next = NULL;
	ft_lstdel(&tmp, ft_token_del);
	if (!cmdlst || !*toks || ((t_token*)(*toks)->content)->type == pipeline)
	{
		ft_dprintf(2, "21sh: unexpected token `|'\n");
		return (1);
	}
	return (0);
}

static void	ft_get_cmd(t_list **toks, t_cmd *cmd)
{
	t_list	*tmp;

	cmd->toks = *toks;
	tmp = *toks;
	cmd->fd_out = 1;
	cmd->fd_err = 2;
	while (*toks && ((t_token*)(*toks)->content)->type != pipeline)
	{
		tmp = *toks;
		*toks = (*toks)->next;
	}
	tmp->next = NULL;
}

t_cmd		*ft_make_cmdlst(t_list **toks)
{
	t_cmd	*cmdlst;
	t_cmd	*tmp;
	t_cmd	cmd;

	cmdlst = NULL;
	while (*toks)
	{
		ft_bzero(&cmd, sizeof(cmd));
		if (((t_token*)(*toks)->content)->type == pipeline
			&& ft_get_pipe(toks, cmdlst))
			return (ft_cmdlst_del(cmdlst));
		ft_get_cmd(toks, &cmd);
		if (!(tmp = ft_cmdlst_push(cmdlst ? tmp : cmdlst, &cmd)))
			return (ft_cmdlst_del(cmdlst));
		!cmdlst ? cmdlst = tmp : 0;
	}
	return (cmdlst);
}
