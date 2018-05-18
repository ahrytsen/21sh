/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:35:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/18 12:24:53 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int			term_print(int c)
{
	return (write(0, &c, 1));
}

t_term		*get_term(void)
{
	static t_term	term;

	return (&term);
}

int		ft_readline_ret(void)
{
	while (get_term()->cursor->next
			&& (get_term()->cursor = get_term()->cursor->next))
		ft_curright(1);
	ft_dprintf(0, "\n");
	return (1);
}

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
	tputs(get_term()->clear, 1, term_print);
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
