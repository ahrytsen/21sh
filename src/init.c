/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:59:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/05 19:17:38 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		cmdline_free(msh_get_environ()->cursor);
		if (isatty(0) && !msh_get_environ()->pid)
		{
			ft_dprintf(2, "\n");
			ft_prompt();
		}
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
	msh_get_environ()->clear = tgetstr("cl", NULL);
	msh_get_environ()->curmov = tgetstr("cm", NULL);
	msh_get_environ()->cm_left = tgetstr("le", NULL);
	msh_get_environ()->cm_right = tgetstr("nd", NULL);
	msh_get_environ()->undln_on = tgetstr("us", NULL);
	msh_get_environ()->undln_off = tgetstr("ue", NULL);
	msh_get_environ()->iv_on = tgetstr("mr", NULL);
	msh_get_environ()->iv_off = tgetstr("me", NULL);
	msh_get_environ()->im_on = tgetstr("im", NULL);
	msh_get_environ()->im_off = tgetstr("ei", NULL);
	msh_get_environ()->del_ch = tgetstr("DC", NULL);
	msh_get_environ()->dm_on = tgetstr("dm", NULL);
	msh_get_environ()->dm_off = tgetstr("ed", NULL);
	msh_get_environ()->height = tgetnum("li");
	msh_get_environ()->width = tgetnum("co");
}

void		ft_init_terminal(int mod)
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
	tcsetattr(0, TCSAFLUSH, mod ? &tty : savetty);
}

void	ft_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	ft_init_signal();
	ft_init_termcap();
	msh_get_environ()->env = ft_strdup_arr(environ);
	msh_get_environ()->cursor = ft_memalloc(sizeof(t_cmdline));
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	ft_setenv("PATH", "/usr/bin:/bin", 0);
}
