/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:35:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/07 21:14:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	ft_get_redirect_in(char **ln, t_token *token)
{
	if (**ln == '<' && !(*(*ln)++ = '\0'))
	{
		if (**ln == '<' && !(*(*ln)++ = '\0'))
			token->type = herestr;
		else if (**ln == '-' && !(*(*ln)++ = '\0'))
			token->type = heredoc_t;
		else
			token->type = heredoc;
	}
	else if (**ln == '>' && !(*(*ln)++ = '\0'))
		token->type = open_file;
	else if (**ln == '&' && !(*(*ln)++ = '\0'))
		token->type = read_in_and;
	else
		token->type = read_in;
}

static void	ft_get_redirect_out(char **ln, t_token *token)
{
	if (**ln == '|' && !(*(*ln)++ = 0))
		token->type = read_out_pipe;
	else if (**ln == '&' && !(*(*ln)++ = 0))
		token->type = read_out_and;
	else if (**ln == '>' && !(*(*ln)++ = 0))
		token->type = read_out_apend;
	else
		token->type = read_out;
}

static void	ft_get_separator(char **ln, t_token *token)
{
	if ((**ln == ' ' || **ln == '\t') && !(*(*ln)++ = '\0'))
		token->type = blank;
	else if ((**ln == ';' || **ln == '\n') && !(*(*ln)++ = '\0'))
		token->type = semicolon;
	else if (**ln == '|' && !(*(*ln)++ = '\0'))
		token->type =
			(**ln == '|' && !(*(*ln)++ = '\0')) ? or : pipeline;
	else if (**ln == '&' && !(*(*ln)++ = '\0'))
	{
		if (**ln == '>' && !(*(*ln)++ = '\0'))
			token->type = and_read_out;
		else
			token->type =
				(**ln == '&' && !(*(*ln)++ = '\0')) ? and : bg_op;
	}
	else if (**ln == '<' && !(*(*ln)++ = '\0')
			&& !(token->data.redir.left = 0))
		ft_get_redirect_in(ln, token);
	else if (**ln == '>' && !(*(*ln)++ = '\0')
			&& (token->data.redir.left = 1))
		ft_get_redirect_out(ln, token);
}

static void	ft_get_token(char **ln, t_token *token)
{
	int	f;

	f = 1;
	token->type = word;
	token->data.word = *ln;
	while (**ln && !ft_isseparator(**ln))
	{
		f && !ft_isdigit(**ln) ? f = 0 : 0;
		if (**ln == '\'' || **ln == '"' || **ln == '`')
			ft_skip_qoutes(ln);
		else if (**ln == '\\')
			ft_skip_slash(ln);
		else
			(*ln)++;
	}
	if ((**ln == '<' || **ln == '>') && f)
	{
		f = **ln;
		*(*ln)++ = '\0';
		token->data.redir.left = ft_atoi(token->data.word);
		(f == '<' ? ft_get_redirect_in : ft_get_redirect_out)(ln, token);
	}
}

t_list		*ft_tokenizer(char *ln)
{
	t_token	tok;
	t_list	*toks;
	t_list	*tmp;

	toks = NULL;
	while (*ln)
	{
		ft_bzero(&tok, sizeof(tok));
		(!ft_isseparator(*ln) ? ft_get_token : ft_get_separator)(&ln, &tok);
		if (tok.type == blank || (!toks && tok.type == semicolon)
			|| (toks && tok.type == semicolon
				&& (((t_token*)tmp->content)->type == semicolon
					|| ((t_token*)tmp->content)->type == bg_op)))
			continue ;
		if (toks && ((t_token*)tmp->content)->type >= heredoc
			&& tok.type == word)
			((t_token*)tmp->content)->data.redir.right = tok.data.word;
		else if (!(tmp =
					ft_lstpush_back(toks ? &tmp : &toks, &tok, sizeof(tok))))
		{
			ft_lstdel(&toks, NULL);
			return (NULL);
		}
	}
	return (toks);
}
