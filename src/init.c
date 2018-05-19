/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:59:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/19 18:19:07 by ahrytsen         ###   ########.fr       */
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
	return ;
}

static void	ft_init_signal(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGSTOP, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGQUIT, sig_handler);
}

static void	ft_init_termcap(void)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		ft_fatal(1, exit,
				"Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatal(1, exit, "Could not access the termcap data base.\n");
	else if (!success)
		ft_fatal(1, exit, "Terminal type `%s' is not defined.\n", termtype);
	get_term()->clear = tgetstr("ce", NULL);
	get_term()->cm_left = tgetstr("le", NULL);
	get_term()->cm_right = tgetstr("nd", NULL);
	get_term()->undln_on = tgetstr("us", NULL);
	get_term()->undln_off = tgetstr("ue", NULL);
	get_term()->iv_on = tgetstr("mr", NULL);
	get_term()->iv_off = tgetstr("me", NULL);
	get_term()->im_on = tgetstr("im", NULL);
	get_term()->im_off = tgetstr("ei", NULL);
	get_term()->del_ch = tgetstr("DC", NULL);
	get_term()->height = tgetnum("li");
	get_term()->width = tgetnum("co");
}

void		ft_terminal(int mod)
{
	static struct termios	*savetty = NULL;
	static struct termios	tty;

	if (!isatty(0))
		ft_fatal(1, exit, "21sh: fd isn't valid terminal type device.\n");
	else if (mod && !savetty)
	{
		if (!(savetty = malloc(sizeof(struct termios))))
			ft_fatal(1, exit, "21sh: malloc fail!\n");
		tcgetattr(0, savetty);
		tty = *savetty;
		tty.c_lflag &= ~(ICANON | ECHO);
		tty.c_cc[VMIN] = 1;
		tty.c_cc[VTIME] = 0;
	}
	tcsetattr(0, mod ? TCSAFLUSH : TCSANOW, mod ? &tty : savetty);
}

void		ft_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	ft_init_signal();
	ft_init_termcap();
	get_term()->cursor = NULL;
	get_term()->hist = NULL;
	get_term()->st_sel = NULL;
	get_term()->end_sel = NULL;
	get_term()->buffer = NULL;
	get_environ()->env = ft_strdup_arr(environ);
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	ft_setenv("PATH", "/usr/bin:/bin", 0);
}
