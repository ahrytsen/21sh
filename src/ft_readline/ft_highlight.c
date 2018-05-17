/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_highlight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:15:10 by ahrytsen          #+#    #+#             */

/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	ft_highlight_redraw(void)
{
	t_line	*cursor;
	uint8_t	f;
	int		count;

	cursor = get_term()->cursor;
	f = 0;
	count = 0;
	while (cursor->prev && (cursor = cursor->prev) && (--count))
		ft_curleft(1);
	while (cursor->next)
	{
		if (cursor == get_term()->st_sel || cursor == get_term()->end_sel)
		{
			f ? ft_dprintf(0, "%s", &cursor->ch) : 0;
			tputs(!f ? get_term()->iv_on : get_term()->iv_off, 1, term_print);
			!f ? ft_dprintf(0, "%s", &cursor->ch) : 0;
			f = !f;
		}
		else
			ft_dprintf(0, "%s", &cursor->ch);
		ft_curright(0);
		cursor = cursor->next;
		count++;
	}
	ft_curnleft(1, count);
	f ? tputs(get_term()->iv_off, 1, term_print) : 0;
}

void		ft_highlight_helper(uint64_t buf)
{
	if (buf != K_SLEFT && buf != K_SRIGHT && buf != K_SUP
		&& buf != K_SDOWN && buf != K_ASLEFT && buf != K_ASRIGHT)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
		ft_highlight_redraw();
	}
}

void		ft_highlight(uint64_t buf)
{
	if (!get_term()->st_sel && !get_term()->end_sel)
		get_term()->st_sel = get_term()->cursor;
	if (buf == K_SRIGHT || buf == K_SDOWN)
		ft_move(buf == K_SRIGHT ? K_RIGHT : K_ADOWN);
	else if (buf == K_SLEFT || buf == K_SUP)
		ft_move(buf == K_SLEFT ? K_LEFT : K_AUP);
	else
		ft_word_action(buf == K_ASRIGHT ? K_ARIGHT : K_ALEFT);
	get_term()->end_sel = get_term()->cursor;
	if (get_term()->st_sel == get_term()->end_sel)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
	}
	ft_highlight_redraw();
}
