/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 12:54:32 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/18 19:26:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	swap_points(void)
{
	t_line	*cursor;
	t_line	*tmp1;
	t_line	*tmp2;

	cursor = get_term()->cursor;
	tmp1 = get_term()->st_sel;
	tmp2 = get_term()->end_sel;
	while (cursor->prev)
		cursor = cursor->prev;
	while (cursor->next)
	{
		if (cursor == tmp1 || cursor == tmp2)
		{
			if (cursor == tmp1)
				return ;
			get_term()->st_sel = tmp2;
			get_term()->end_sel = tmp1;
			return ;
		}
		cursor = cursor->next;
	}
}

void		line_cute(void)
{
	t_line	*st;
	t_line	*end;
	t_line	*tmp;

	swap_points();
	get_term()->buffer ? line_tostr(&get_term()->buffer, 2) : 0;
	st = get_term()->st_sel;
	end = get_term()->end_sel;
	get_term()->buffer = st;
	tmp = st->prev;
	st->prev = NULL;
	tmp ? tmp->next = end : 0;
	get_term()->cursor = end;
	end->prev->next = NULL;
	end->prev = tmp;
}

int			line_copy(void)
{
	swap_points();
	get_term()->buffer ? line_tostr(&get_term()->buffer, 2) : 0;
	if (!(get_term()->buffer = ft_memalloc(sizeof(t_line))))
		return (-1);
	while (get_term()->st_sel != get_term()->end_sel)
	{
		if (line_add(get_term()->buffer, get_term()->st_sel->ch) == -1)
			return (!line_tostr(&get_term()->buffer, 2) ? -1 : 0);
		get_term()->st_sel = get_term()->st_sel->next;
	}
	get_term()->buffer = get_term()->buffer->prev;
	ft_memdel((void**)&get_term()->buffer->next);
	while (get_term()->buffer->prev)
		get_term()->buffer = get_term()->buffer->prev;
	return (1);
}

void		line_paste(void)
{
	t_line	*tmp;

	tmp = get_term()->cursor->prev;
	tmp ? tmp->next = get_term()->buffer : 0;
	get_term()->buffer->prev = tmp;
	while (get_term()->buffer->next)
		get_term()->buffer = get_term()->buffer->next;
	get_term()->buffer->next = get_term()->cursor;
	get_term()->cursor->prev = get_term()->buffer;
	get_term()->st_sel = get_term()->buffer;
	get_term()->end_sel = get_term()->buffer;
	get_term()->buffer = NULL;
}
