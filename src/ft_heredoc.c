/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:00:10 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/24 19:44:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_heredoc(t_list *toks)
{
	t_token	*tok;
	int		ret;

	get_term()->prompt = P_HEREDOC;
	while (toks)
	{
		tok = toks->content;
		if (tok->type == heredoc || tok->type == heredoc_t)
			if (!(ret = ft_heredoc_toread(tok)))
				break ;
		toks = toks->next;
	}
	get_term()->prompt = P_USER;
	return (ret);
}

int		ft_heredoc_toread(t_token *tok)
{
	int		ret;
	char	*line;

	line = NULL;
	get_term()->heredoc_key = tok->data.redir.right;
	tok->data.redir.right = NULL;
	while ((ret = ft_readline(0, &line)) > 0)
	{
		if (!ft_strcmp(line, get_term()->heredoc_key))
			break ;
		tok->data.redir.right = ft_strextend(tok->data.redir.right, line);
		line = ft_strjoin(tok->data.redir.right, "\n");
		free(tok->data.redir.right);
		tok->data.redir.right = line;
		line = NULL;
	}
	free(line);
	return (ret == -1 ? 0 : 1);
}
