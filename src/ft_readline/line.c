/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:25:08 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/11 20:48:45 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char	*line_tostr(t_line **cursor, int mod)
{
	size_t	size;
	char	*line;
	t_line	*tmp;

	size = 1;
	line = NULL;
	tmp = *cursor;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		size += ft_strlen((char*)&tmp->ch);
		tmp = tmp->prev;
	}
	if (mod != 2 && !(line = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	while (tmp->ch)
	{
		mod != 2 ? ft_strcat(line, (char*)&tmp->ch) : 0;
		tmp = tmp->next;
		mod ? ft_memdel((void**)&tmp->prev) : 0;
	}
	mod ? *cursor = tmp : 0;
	return (line);
}

int		line_bs(t_line *cursor)
{
	t_line	*tmp;

	if (!(tmp = cursor->prev))
		return (1);
	tmp = tmp->prev;
	ft_memdel((void**)&cursor->prev);
	cursor->prev = tmp;
	tmp ? tmp->next = cursor : 0;
	return (0);
}

int		line_add(t_line *cursor, uint64_t ch)
{
	t_line	*tmp;
	t_line	*new_ch;

	if (!(new_ch = ft_memalloc(sizeof(*new_ch))))
		return (1);
	new_ch->ch = ch;
	tmp = cursor->prev;
	cursor->prev = new_ch;
	new_ch->next = cursor;
	new_ch->prev = tmp;
	if (tmp)
		tmp->next = new_ch;
	return (0);
}
