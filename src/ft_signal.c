/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:41:23 by ahrytsen          #+#    #+#             */
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

static void	sigtstp_handler(int signo)
{
	t_list		*proc;

	if (signo == SIGTSTP)
	{
		if (get_environ()->pid > 1 && (proc = ft_memalloc(sizeof(t_list))))
		{
			kill(SIGSTOP, get_environ()->pid);
			setpgid(get_environ()->pid, get_environ()->pid);
			proc->content_size = get_environ()->pid;
			ft_lstadd(&get_environ()->proc, proc);
		}
		else
			ft_dprintf(2, "\a");
	}
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
			ft_readline_ret();
	}
	else if (signo == SIGWINCH)
	{
		ft_curhome();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		get_term()->height = w.ws_row;
		get_term()->width = w.ws_col;
		ft_redraw_line();
	}
}

void		ft_init_signal_chld(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	get_environ()->sh_pid = getpid();
	setpgid(get_environ()->sh_pid, get_environ()->sh_pid);
	tcsetpgrp(1, get_environ()->sh_pid);
}


void		ft_init_signal(void)
{
	struct sigaction int_handler;

	ft_bzero(&int_handler, sizeof(struct sigaction));
	int_handler.sa_handler = sig_handler;
	sigaction(SIGINT, &int_handler, 0);
	signal(SIGWINCH, sig_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGQUIT, sig_handler);
	get_environ()->sh_pid = getpid();
	setpgid(get_environ()->sh_pid, get_environ()->sh_pid);
	tcsetpgrp(1, get_environ()->sh_pid);
}
