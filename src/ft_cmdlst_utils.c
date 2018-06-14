/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:35:56 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/14 17:17:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

t_cmd			*ft_cmdlst_del(t_cmd *cmdlst)
{
	t_cmd	*tmp;

	while (cmdlst)
	{
		tmp = cmdlst;
		cmdlst = cmdlst->next;
		ft_strarr_free(tmp->av);
		ft_lstdel(&tmp->toks, ft_token_del);
		free(tmp);
	}
	return (NULL);
}

t_cmd			*ft_cmdlst_push(t_cmd *cmdlst, t_cmd *node)
{
	t_cmd *new_node;

	if (!(new_node = (t_cmd*)malloc(sizeof(t_cmd)))
		&& ft_dprintf(2, "21sh: malloc error\n"))
		return (ft_cmdlst_del(cmdlst));
	ft_memcpy(new_node, node, sizeof(t_cmd));
	while (cmdlst && cmdlst->next)
		cmdlst = cmdlst->next;
	cmdlst ? cmdlst->next = new_node : 0;
	new_node->prev = cmdlst;
	return (new_node);
}
