/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_paste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 12:44:24 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/18 19:19:50 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_copy_paste(uint64_t buf)
{
/*	if ((!get_term()->st_sel || !get_term()->end_sel)
		|| get_term()->st_sel == get_term()->end_sel)
		return (ft_dprintf(0, "\a"));*/
	buf != K_COPY ? ft_curhome(1) : 0;
	if (buf == K_CUTE)
		line_cute();
	else if (buf == K_PASTE)
		line_paste();
	else if (line_copy() == -1)
		return (-1);
	return (buf);
}
