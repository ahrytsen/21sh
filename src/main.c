/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:53:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/14 20:54:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	test(t_list *elem)
{
	t_token	*tok = elem->content;

	if (tok->type == word)
		ft_printf("[%s]", tok->data.word);
	else
	{
		ft_printf("[%d", tok->data.redir.left);
		if (tok->type == heredoc)
			ft_printf(" <-*heredoc*-> ");
		else if (tok->type == heredoc_t)
			ft_printf(" <-*heredoc_t*-> ");
		else if (tok->type == herestr)
			ft_printf(" <-*herestr*-> ");
		else if (tok->type == open_file)
			ft_printf(" <-*open_file*-> ");
		else if (tok->type == read_in)
			ft_printf(" <-*read_in*-> ");
		else if (tok->type == read_in_and)
			ft_printf(" <-*read_in_and*-> ");
		else if (tok->type == read_out)
			ft_printf(" <-*read_out*-> ");
		else if (tok->type == read_out_and)
			ft_printf(" <-*read_out_and*-> ");
		else if (tok->type == read_out_pipe)
			ft_printf(" <-*read_out_pipe*-> ");
		else if (tok->type == and_read_out)
			ft_printf(" <-*and_read_out*-> ");
		else if (tok->type == read_out_apend)
			ft_printf(" <-*read_out_apend*-> ");
		ft_printf("%s]", tok->data.redir.right);
	}
}

void	test_ast(t_ast *ast)
{
	t_cmd	*tmp;

	if (!ast)
		return ;
	test_ast(ast->right);
	if (ast->type == ast_and)
		ft_printf("[&&]");
	else if (ast->type == ast_or)
		ft_printf("[||]");
	else if (ast->type == ast_bg)
		ft_printf("[&]");
	else if (ast->type == ast_smcln)
		ft_printf("[;]");
	else
	{
		tmp = ast->cmd;
		while (tmp)
		{
			ft_lstiter(tmp->toks, test);
			tmp = tmp->next;
			tmp ? ft_printf("[|]") : 0;
		}
	}
	test_ast(ast->left);
}

int		main_loop(void)
{
	char	*cmds;
	t_list	*toks;
	t_ast	*ast;
	int		i;

	while (1)
	{
		if (!(i = ft_readline(0, &cmds)) || i == -1)
			return (!i ? get_environ()->st : 1);
		toks = ft_tokenize(cmds);
		ast = ft_ast_make(&toks);
		//test_ast(ast);
		//ast ? ft_printf("\n") : 0;
		ft_lstdel(&toks, ft_token_del);
		get_environ()->st = ft_ast_exec(ast);
		ast = ft_ast_del(ast, 1);
		free(cmds);
	}
}

int		main(void)
{
	ft_init();
	return (main_loop());
}
