/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:16:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/14 20:42:23 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static char	*ft_tokename(t_ast *node)
{
	if (node->type == ast_and)
		return ("&&");
	else if (node->type == ast_or)
		return ("||");
	else if (node->type == ast_bg)
		return ("&");
	else if (node->type == ast_smcln)
		return (";");
	else
		return ("cmd");
}

static int	ft_isoperator(t_token *tok)
{
	return ((tok->type >= bg_op && tok->type <= or) ? 1 : 0);
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
	ft_lstdel(&tmp, ft_token_del);
}

static void	ft_get_cmd(t_list **toks, t_ast *ast_node)
{
	t_list	*tmp;

	ast_node->toks = *toks;
	ast_node->type = cmd;
	while (*toks && !ft_isoperator((*toks)->content))
	{
		tmp = *toks;
		*toks = (*toks)->next;
	}
	tmp->next = NULL;
}

t_ast		*ft_ast_make(t_list **toks)
{
	t_ast	*ast;
	t_ast	*tmp;
	t_ast	ast_node;

	ast = NULL;
	while (*toks)
	{
		ft_bzero(&ast_node, sizeof(ast_node));
		(ft_isoperator((*toks)->content)
		? ft_get_operator : ft_get_cmd)(toks, &ast_node);
		if (((ast_node.type > cmd && (!ast || ast->type > cmd)) && ft_dprintf(2,
					"21sh: unexpected token `%s'\n", ft_tokename(&ast_node)))
			|| !(tmp = ft_ast_push(ast, &ast_node)))
		{
			ft_lstdel(&ast_node.toks, ft_token_del);
			return (ft_ast_del(ast, 1));
		}
		ast = tmp;
	}
	if (ast && ast->type != cmd && ast->type != ast_smcln
		&& ft_dprintf(2, "21sh: unexpected EOF\n"))
		return (ft_ast_del(ast, 1));
	while (ast && ast->prev)
		ast = ast->prev;
	return (ast);
}
