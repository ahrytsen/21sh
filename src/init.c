/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:59:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/04 16:56:41 by ahrytsen         ###   ########.fr       */
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

void	ft_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	ft_init_signal();
	msh_get_environ()->env = ft_strdup_arr(environ);
	msh_get_environ()->cursor = ft_memalloc(sizeof(t_cmdline));
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	ft_setenv("PATH", "/usr/bin:/bin", 0);
}

void		ft_init_termcap(void)
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
	g_term.clear = tgetstr("cl", NULL);
	g_term.curmov = tgetstr("cm", NULL);
	g_term.undln_on = tgetstr("us", NULL);
	g_term.undln_off = tgetstr("ue", NULL);
	g_term.iv_on = tgetstr("mr", NULL);
	g_term.iv_off = tgetstr("me", NULL);
	g_term.height = tgetnum("li");
	g_term.width = tgetnum("co");
}

void		ft_init_terminal(int mod)
{
	static struct termios	savetty;
	static struct termios	tty;

	if (!isatty(0))
		ft_fatal(1, exit, "ft_select: fd isn't valid terminal type device.\n");
	if (!mod)
	{
		tputs(tgetstr("ve", NULL), 1, term_print);
		tputs(tgetstr("te", NULL), 1, term_print);
	}
	else if (mod == 1)
	{
		tcgetattr(0, &tty);
		savetty = tty;
		tty.c_lflag &= ~(ICANON | ECHO);
		tty.c_cc[VMIN] = 1;
		tty.c_cc[VTIME] = 0;
	}
	mod ? ft_init_signal() : 0;
	mod ? tputs(tgetstr("vi", NULL), 1, term_print) : 0;
	mod ? tputs(tgetstr("ti", NULL), 1, term_print) : 0;
	tcsetattr(0, TCSAFLUSH, mod ? &tty : &savetty);
}
