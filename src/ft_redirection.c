/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:04:03 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/28 17:40:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	ft_redir_fd(t_token *tok)
{
	int	fd;
	int	flg;

	flg = ft_redir_right_param(tok);
	if (tok->type == and_read_out
		|| (tok->type == read_out_and && tok->data.redir.left == 1 && !flg))
	{
		fd = open(tok->data.redir.right, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, 1);
		dup2(fd, 2);
	}
	else
	{
		tok->data.redir.nbr != -1
			? dup2(tok->data.redir.nbr, tok->data.redir.left) : 0;
		if (tok->data.redir.cls)
			close(tok->data.redir.nbr != -1
				? tok->data.redir.nbr : tok->data.redir.left);
	}
}

static void	ft_redir_heredoc(t_token *tok)
{
	int	pl[2];

	if (pipe(pl) && ft_printf("21sh: pipe error\n"))
		return ;
	dup2(pl[0], tok->data.redir.left);
	close(pl[0]);
	ft_dprintf(pl[1], tok->type == herestr ? "%s\n" : "%s", tok->data.redir.hd);
	close(pl[1]);
}

static void	ft_redir_file(t_token *tok)
{
	int	oflag;
	int	fd;

	oflag = 0;
	fd = 0;
	if (tok->type == open_file)
		oflag |= O_RDWR | O_CREAT;
	else if (tok->type == read_in)
		access(tok->data.redir.right, F_OK)
			? (fd = ft_dprintf(2, "21sh: no such file or directory: %s\n",
							tok->data.redir.right)) : (oflag |= O_RDONLY);
	else
		oflag |= O_WRONLY | O_CREAT | (tok->type == read_out_apend
										? O_APPEND : O_TRUNC);
	if (!fd && (fd = open(tok->data.redir.right,
							oflag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
	{
		dup2(fd, tok->data.redir.left);
		close(fd);
	}
	else if (fd < 0)
		ft_dprintf(2, "21sh: open() error\n");
}

void		ft_redirection_close(t_list *toks)
{
	t_token	*token;

	while (toks)
	{
		token = toks->content;
		if (token->type > or)
			token->data.redir.left > 2 ? close(token->data.redir.left) : 0;
		toks = toks->next;
	}
}

void		ft_redirection(t_list *toks)
{
	t_token	*token;

	while (toks)
	{
		token = toks->content;
		if (token->type > or && token->type < open_file)
			ft_redir_heredoc(token);
		else if (token->type >= open_file && token->type <= read_in)
			ft_redir_file(token);
		else if (token->type > read_in)
			ft_redir_fd(token);
		toks = toks->next;
	}
}
