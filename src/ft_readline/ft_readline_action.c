/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:20:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/10 20:52:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void	ft_back_space(void)
{
	if (!line_bs(get_term()->cursor))
	{
		//tputs(tgetstr("dm", NULL), 1, term_print);
		tputs(get_term()->cm_left, 1, term_print);
		!get_term()->curpos ? tputs(get_term()->cm_left, 1, term_print) : 0;
		tputs(tparm(get_term()->del_ch, 1), 1, term_print);
		(!get_term()->curpos) ? get_term()->curpos = get_term()->width - 1
			: get_term()->curpos--;
		//tputs(tgetstr("ed", NULL), 1, term_print);
	}
	else
		ft_dprintf(0, "\a");
}

void	ft_move(uint64_t buf)
{
	if (buf == 0X445B1B && get_term()->cursor->prev)
	{
		tputs(get_term()->cm_left, 1, term_print);
		get_term()->cursor = get_term()->cursor->prev;
		get_term()->curpos--;
	}
	else if (buf == 0X435B1B && get_term()->cursor->next)
	{
		tputs(get_term()->cm_right, 1, term_print);
		get_term()->cursor = get_term()->cursor->next;
		get_term()->curpos++;
	}
	else
		ft_dprintf(0, "\a");
}

void	ft_print_tail(t_line *cursor)
{
	int	curpos;

	curpos = get_term()->curpos;
	while (cursor->next)
	{
		if (curpos == get_term()->width - 1)
		{
			tputs(get_term()->cm_right, 1, term_print);
			curpos = 0;
		}
		ft_dprintf(0, "%s", (char*)&cursor->ch);
		cursor =  cursor->next;
		curpos++;
	}
	while (cursor != get_term()->cursor)
	{
		tputs(get_term()->cm_left, 1, term_print);
		cursor =  cursor->prev;
	}
}

void	ft_add(uint64_t buf)
{
	if ((buf > 31 && buf < 127) || ft_iswhitespace(buf))
	{
		ft_dprintf(0, "%s", &buf);
		line_add(get_term()->cursor, buf);
		get_term()->curpos++;
		if (get_term()->curpos == get_term()->width - 1)
		{
			get_term()->curpos = 0;
			tputs(get_term()->cm_right, 1, term_print);
		}
		ft_print_tail(get_term()->cursor);
	}
	else
		ft_dprintf(0, "\a");
}
