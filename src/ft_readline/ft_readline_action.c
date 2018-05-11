/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:20:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/11 20:54:39 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_del(void)
{
	if (!get_term()->cursor->next && !get_term()->cursor->prev)
		return (1);
	else if (get_term()->cursor->next)
	{
		get_term()->cursor = get_term()->cursor->next;
		ft_curright(1);
		ft_back_space();
	}
	else
		ft_dprintf(0, "\a");
	return (0);
}

void	ft_back_space(void)
{
	if (!line_bs(get_term()->cursor))
	{
		ft_curleft(1);
		tputs(tparm(get_term()->del_ch, 1), 1, term_print);
		ft_print_tail(get_term()->cursor);
	}
	else
		ft_dprintf(0, "\a");
}

void	ft_move(uint64_t buf)
{
	if (buf == 0X445B1B && get_term()->cursor->prev)
	{
		ft_curleft(1);
		get_term()->cursor = get_term()->cursor->prev;
	}
	else if (buf == 0X435B1B && get_term()->cursor->next)
	{
		ft_curright(1);
		get_term()->cursor = get_term()->cursor->next;
	}
	else
		ft_dprintf(0, "\a");
}

void	ft_add(uint64_t buf)
{
	if ((buf > 31 && buf < 127) || ft_iswhitespace(buf))
	{
		ft_dprintf(0, "%s", &buf);
		ft_curright(0);
		line_add(get_term()->cursor, buf);
		get_term()->cursor->ch ? ft_print_tail(get_term()->cursor) : 0;
	}
	else
		ft_dprintf(0, "\a");
}
