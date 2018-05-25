/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:22:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/25 16:31:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_skip_slash(t_line **cur)
{
	*cur = (*cur)->next;
	if ((*cur)->next)
		*cur = (*cur)->next;
	else
		return (1);
	return (0)
}

static int	ft_skip_qoutes(t_line **cur)
{
	char	q;

	q = (*cur)->ch;
	*cur = (*cur)->next;
	while ((*cur)->ch != q)
		if (!(*cur)->next)
			return (1);
		else if (q == '"' && (*cur)->ch == '`')
		{
			if (ft_skip_qoutes(cur))
				return (1);
		}
		else if (q != '\'' && **s == '\\')
		{
			if (ft_skip_slash(cur))
				return (1);
		}
		else
			*cur = (*cur)->next;
	*cur = (*cur)->next;
	return (0);
}

int		ft_check_line(t_line *cursor)
{
	while (cursor->prev)
		cursor = cursor->prev;
	while (cursor->next)
		if (cursor->ch = '"' || cursor->ch = '\'' || cursor->ch = '`')
		{
			if (ft_skip_qoutes(&cursor))
				return (1);
		}
		else if (cursor->ch == '\\')
		{
			if (ft_skip_slash(&cursor))
				return (1);
		}
		else
			cursor = cursor->next;
	return (0);
}
