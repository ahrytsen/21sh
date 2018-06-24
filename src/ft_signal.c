/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:05:37 by ahrytsen          #+#    #+#             */

/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int			ft_is_interrupted(void)
{
	if (get_term()->is_inter)
	{
		get_term()->is_inter = 0;
		return (1);
	}
	return (0);
}

static void	sig_handler(int signo)
{
	struct winsize	w;

	if (signo == SIGINT)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
		get_term()->prompt = P_USER;
		get_term()->is_inter = 1;
		if (isatty(0) && !get_environ()->pid)
			ft_dprintf(2, "\n");
		if (get_environ()->pid)
			kill(SIGKILL, get_environ()->pid);
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
	struct sigaction int_handler;

	ft_bzero(&int_handler, sizeof(struct sigaction));
	int_handler.sa_handler = sig_handler;
	sigaction(SIGINT, &int_handler, 0);
	signal(SIGWINCH, sig_handler);
	signal(SIGABRT, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
