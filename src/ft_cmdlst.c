/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:53:42 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/11 20:14:31 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	ft_get_cmd(t_list **toks, t_cmd *cmd)
{
	t_list	*tmp;

	cmd->toks = *toks;
	while (*toks && !ft_isoperator((*toks)->content))
	{
		tmp = *toks;
		*toks = (*toks)->next;
	}
	tmp->next = NULL;
}

t_cmd	*ft_make_cmdlst(t_list *toks)
{
	t_cmd	*cmd_lst;
	t_cmd	*tmp;
	t_cmd	cmd;

	cmd_lst = NULL;
	while (toks)
	{
		ft_bzero(&cmd, sizeof(cmd));

		((t_token*)toks->content)->type != pipeline
			? ft_get_cmd(&toks, &cmd) : 0;

	}
	return (NULL);
}
