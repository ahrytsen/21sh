/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:22:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/23 21:54:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	skip_slash(char **ln)
{
	(*ln)++;
	if (**ln)
		(*ln)++;
	else
	{
		get_term()->prompt = P_BSLASH;
		return (1);
	}
	return (0);
}

static int	skip_qoutes(char **ln)
{
	char	q;

	q = *(*ln)++;
	while (**ln != q)
		if (!**ln)
		{
			get_term()->prompt = q;
			return (1);
		}
		else if (q == '"' && **ln == '`')
		{
			if (skip_qoutes(ln))
				return (1);
		}
		else if (q != '\'' && **ln == '\\')
		{
			if (skip_slash(ln))
				return (1);
		}
		else
			(*ln)++;
	(*ln)++;
	return (0);
}

int			ft_check_line(char *ln)
{
	if (get_term()->prompt == P_HEREDOC)
		return (ln ? 0 : 1);
	if (!ln)
	{
		get_term()->prompt = P_USER;
		return (1);
	}
	while (*ln)
		if (*ln == '"' || *ln == '\'' || *ln == '`')
		{
			if (skip_qoutes(&ln))
				return (1);
		}
		else if (*ln == '\\')
		{
			if (skip_slash(&ln))
				return (1);
		}
		else
			ln++;
	get_term()->prompt = P_USER;
	return (0);
}
