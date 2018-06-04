/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:35:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/04 19:47:33 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void		ft_skip_slash(char **s)
{
	if (*++(*s))
		(*s)++;
}

static void		ft_skip_qoutes(char **s)
{
	char	q;

	q = *(*s)++;
	while (**s != q)
		if (!**s)
			return ;
		else if (q == '"' && **s == '`')
			ft_skip_qoutes(s);
		else if (q != '\'' && **s == '\\' && (*s)++)
			**s ? (*s)++ : 0;
		else
			(*s)++;
	(*s)++;
}

static void	ft_get_separator(char **ln, t_token *token)
{
	if (**ln == ' ' || **ln == '\t')
		token->type = blank;
	else if (**ln == ';' || **ln == '\n')
		token->type = semicolon;
	else if (**ln == '|')
		token->type = ft_strnequ(*ln, "||", 2) ? or : pipeline;
	else if (**ln == '&')
		token->type = ft_strnequ(*ln, "&&", 2) ? and : bg_op;
	else if (**ln == '<')
		token->type = ft_strnequ(*ln, "<<", 2) ? heredoc : read_in;
	else if (**ln == '>')
		token->type = ft_strnequ(*ln, ">>", 2) ? read_out_apend : read_out;
	**ln = 0;
	*ln += (token->type == read_out_apend || token->type == or
			|| token->type == and || token->type == heredoc) ? 2 : 1;
}

static void	ft_get_token(char **ln, t_token *token)
{
	token->type = word;
	token->data.word = *ln;
	while (**ln && !ft_isseparator(**ln))
		if (**ln == '\'' || **ln == '"' || **ln == '`')
			ft_skip_qoutes(ln);
		else if (**ln == '\\')
			ft_skip_slash(ln);
		else
			(*ln)++;
}

t_list	*ft_tokenizer(char *ln)
{
	int		i;
	t_token	tok;
	t_list	*toks;
	t_list  *tmp;

	i = 0;
	toks = NULL;
	while(*ln && ++i)
	{
		(!ft_isseparator(*ln) ? ft_get_token : ft_get_separator)(&ln, &tok);
		if ((tok.type == semicolon || tok.type == blank)
			&& tok.type == ((t_token*)tmp->content)->type)
			continue ;
		if (!(tmp = ft_lstpush_back(toks ? &tmp : &toks, &tok, sizeof(tok))))
		{
			ft_lstdel(&toks, NULL);
			return (NULL);
		}
	}
	return (toks);
}
