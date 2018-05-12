/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:35:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/12 18:10:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	ft_redraw_line(void)
{
	while (get_term()->cursor->prev)
		get_term()->cursor = get_term()->cursor->prev;
	while (get_term()->cursor->next)
	{
		ft_dprintf(0, "%s", &get_term()->cursor->ch);
		ft_curright(0);
		get_term()->cursor = get_term()->cursor->next;
	}
}

void	ft_print_tail(t_line *cursor)
{
	int	count;

	count = 0;
	while (cursor->next)
	{
		ft_dprintf(0, "%s", &cursor->ch);
		ft_curright(0);
		cursor = cursor->next;
		count++;
	}
	tputs(get_term()->clear, 1, term_print);
	ft_curnleft(1, count);
}
