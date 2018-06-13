/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:11:31 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/12 19:11:35 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	ft_token_del(void *token, size_t size)
{
	(void)size;
	free(token);
}

int		ft_isseparator(int c)
{
	return (ft_strchr("|&;()<> \t\n", c) ? 1 : 0);
}

int		ft_is_fd(t_token *tok)
{
	char	*tmp;

	tmp = tok->data.word;
	while (*tmp)
		if (!ft_isdigit(*tmp++))
			return (0);
	return (1);
}

void	ft_skip_slash(char **s)
{
	if (*++(*s))
		(*s)++;
}

void	ft_skip_qoutes(char **s)
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