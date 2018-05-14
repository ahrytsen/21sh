/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:05:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/14 21:23:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		hist_init(void)
{
	t_hist	*new_hist;

	if (!(new_hist = ft_memalloc(sizeof(t_hist))))
		return (-1);
	if (!get_term()->hist)
		get_term()->hist = new_hist;
	else
	{
		get_term()->hist->next = new_hist;
		new_hist->prev = get_term()->hist;
		get_term()->hist = new_hist;
	}
	get_term()->hist->tmp = get_term()->cursor;
	return (1);
}

void	hist_move(uint64_t buf)
{
	t_hist	*tmp;

	tmp = (buf == K_UP ? get_term()->hist->prev : get_term()->hist->next);
	if (tmp)
	{
		get_term()->hist = tmp;
		if (!get_term()->hist->tmp)
			get_term()->hist->tmp = copy_line(get_term()->hist->line);
		ft_curhome(0);
		get_term()->hist->tmp ? get_term()->cursor = get_term()->hist->tmp : 0;
		ft_redraw_line();
	}
	else
		ft_dprintf(0, "\a");
}

void	hist_commit(int st)
{
	t_line	*to_save;

	to_save = get_term()->cursor;
	get_term()->hist->tmp = NULL;
	while (get_term()->hist->prev)
		get_term()->hist = get_term()->hist->prev;
	while (get_term()->hist->next)
	{
		if (get_term()->hist->tmp)
			line_tostr(&get_term()->hist->tmp, 2);
		get_term()->hist = get_term()->hist->next;
	}
	if (get_term()->hist->tmp)
			line_tostr(&get_term()->hist->tmp, 2);
	get_term()->cursor = ft_memalloc(sizeof(t_line));
	get_term()->hist->line = to_save;
}
