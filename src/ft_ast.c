/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:16:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/08 19:03:34 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_isoperator(t_token *tok)
{
	return (tok->type >= bg_op && tok->type <= or ? 1 : 0);
}

static void	ft_get_operator(t_list **toks, t_ast *ast_node)
{
	t_list	*tmp;
	t_token	*tok;

	tmp = *toks;
	*toks = (*toks)->next;
	tmp->next = NULL;
	tok = tmp->content;
	if (tok->type == bg_op)
		ast_node->type = ast_bg;
	else if (tok->type == semicolon)
		ast_node->type = ast_smcln;
	else if (tok->type == and)
		ast_node->type = ast_and;
	else if (tok->type == or)
		ast_node->type = ast_or;
	ft_lstdel(&tmp, NULL);
}

static void	ft_get_cmd(t_list **toks, t_ast *ast_node)
{

}

t_ast		*ft_make_ast(t_list *toks)
{
	t_ast	*ast_head;
	t_ast	ast_node;
	t_list	*prev_tok;

	ast_head = NULL;
	prev_tok = NULL;
	while (toks)
	{
		ft_bzero(&ast_node, sizeof(ast_node));
		if (ft_isoperator(toks->content))
		{
			if (!prev_tok || ft_isoperator(prev_tok->content))
				return (NULL);
			prev_tok->next = NULL;
			ft_get_operator(&toks, &ast_node);
		}
		prev_tok = toks;
		toks = toks->next;
	}
}
