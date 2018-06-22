/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:05:37 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/22 20:00:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	sig_handler(int signo)
{
	struct winsize	w;

	if (signo == SIGINT)
	{
		clean_hist();
		hist_init();
		free(line_tostr(&get_term()->cursor, 1));
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
		ft_memdel((void**)&get_term()->res);
		get_term()->prompt = P_USER;
		if (isatty(0) && !get_environ()->pid)
		{
			ft_dprintf(2, "\n");
			ft_prompt();
		}
	}
	else if (signo == SIGWINCH)
	{
		ft_curhome();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		get_term()->height = w.ws_row;
		get_term()->width = w.ws_col;
		ft_redraw_line();
	}
	else if (signo == SIGTSTP)
	{
		if (get_environ()->pid)
			kill(SIGSTOP, get_environ()->pid);
	}
}

void		ft_init_signal(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
}
