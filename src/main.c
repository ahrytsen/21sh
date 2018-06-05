/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:53:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/05 20:39:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	test(t_list *elem)
{
	t_token	*tok = elem->content;

	if (tok->type == blank)
		ft_printf(" *blank* ");
	else if (tok->type == word)
		ft_printf("%s", tok->data.word);
	else if (tok->type == pipeline)
		ft_printf(" *pipe* ");
	else if (tok->type == bg_op)
		ft_printf(" *bg_op* ");
	else if (tok->type == semicolon)
		ft_printf(" *semicolon* ");
	else if (tok->type == and)
		ft_printf(" *and* ");
	else if (tok->type == or)
		ft_printf(" *or* ");
	else if (tok->type == heredoc)
		ft_printf(" *heredoc* ");
	else if (tok->type == heredoc_t)
		ft_printf(" *heredoc_t* ");
	else if (tok->type == herestr)
		ft_printf(" *herestr* ");
	else if (tok->type == open_file)
		ft_printf(" *open_file* ");
	else if (tok->type == read_in)
		ft_printf(" *read_in* ");
	else if (tok->type == read_in_and)
		ft_printf(" *read_in_and* ");
	else if (tok->type == read_out)
		ft_printf(" *read_out* ");
	else if (tok->type == read_out_and)
		ft_printf(" *read_out_and* ");
	else if (tok->type == read_out_pipe)
		ft_printf(" *read_out_pipe* ");
	else if (tok->type == and_read_out)
		ft_printf(" *and_read_out* ");
	else if (tok->type == read_out_apend)
		ft_printf(" *read_out_apend* ");
	else
		ft_printf(" *unknown* ");
	!elem->next ? ft_printf("\n") : 0;
	free(tok);
}

int		main_loop(void)
{
	char	*cmds;
//	char	**cmd;
	t_list	*toks;
	int		i;

	while (1)
	{
		i = ft_readline(0, &cmds);
		if (!i || i == -1)
			return (!i ? get_environ()->st : 1);
		toks = ft_tokenizer(cmds);
		ft_lstiter(toks, test);
		ft_lstdel(&toks, NULL);
/*		i = 0;
		cmd = msh_splitsemicolon(cmds);
		while (cmd && cmd[i])
		{
			get_environ()->st = ft_exec(msh_splitwhitespaces(cmd[i]), NULL);
			free(cmd[i++]);
		}
		free(cmd);*/
		free(cmds);
	}
}

int		main(void)
{
	ft_init();
	return (main_loop());
}
