/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:04:03 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/18 21:33:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	ft_tofile_redir(t_token *tok)
{
	int	oflag;
	int	fd;

	oflag = 0;
	if (tok->type == open_file)
		oflag |= O_RDWR | O_CREAT;
	else if (tok->type >= read_out && tok->type < and_read_out)
		oflag |= O_WRONLY | O_CREAT | (tok->type == read_out_apend ? O_APPEND : 0);
	fd = open(tok->data.redir.right,
			oflag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd, tok->data.redir.left);
	close(fd);
}

void	ft_redirection_close(t_list *toks)
{
	t_token	*token;

	while (toks)
	{
		token = toks->content;
		if (token->type >= heredoc)
			close(token->data.redir.left);
		toks = toks->next;
	}
}

void	ft_redirection(t_list *toks)
{
	t_token	*token;

	while (toks)
	{
		token = toks->content;
		if (token->type >= heredoc && token->type < open_file)
			(void)toks;
		else if (token->type >= open_file)
			ft_tofile_redir(token);
		toks = toks->next;
	}
}
