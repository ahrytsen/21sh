/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/25 16:44:19 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_clearscreen(void)
{
	tputs(tgetstr("cl", NULL), 1, term_print);
	ft_redraw_line();
	return (1);
}

static int	ft_check_key(uint64_t buf)
{
	if (buf == K_AUP || buf == K_ADOWN || buf == K_RIGHT || buf == K_LEFT
		|| buf == K_HOME || buf == K_END)
		return (K_MOVE);
	else if (buf == K_ALEFT || buf == K_ARIGHT || buf == K_ABS || buf == K_ADEL)
		return (K_WORD_MOVE);
	else if (buf == K_SLEFT || buf == K_SUP || buf == K_ASLEFT
			|| buf == K_SRIGHT || buf == K_SDOWN || buf == K_ASRIGHT)
		return (K_SELECT);
	return (0);
}

static int	ft_action(uint64_t buf)
{
	if (buf == K_RET)
		ft_readline_ret();
	else if (buf == 4)
		buf = ft_del();
	else if (buf == K_TAB)
		ft_autocomplit(get_term()->cursor);
	else if (buf == K_BS)
		ft_back_space();
	else if (ft_check_key(buf) == K_MOVE)
		ft_move(buf);
	else if (ft_check_key(buf) == K_WORD_MOVE)
		ft_word_action(buf);
	else if (buf == K_UP || buf == K_DOWN)
		hist_move(buf);
	else if (ft_check_key(buf) == K_SELECT)
		ft_highlight(buf);
	else if (buf == K_COPY || buf == K_CUTE || buf == K_PASTE)
		buf = ft_copy_paste(buf);
	else if (buf == 12)
		return (ft_clearscreen());
	else if (((char*)&buf)[0] != 27 && (buf > 31 || ft_iswhitespace(buf)))
		buf = ft_add(buf);
	else
		ft_dprintf(0, "\a");
	return (ft_highlight_helper(buf));
}

/*int			ft_readline_toread(const int fd, char **line)
{

}*/

int			ft_readline(const int fd, char **line)
{
	int				ret;
	uint64_t		buf;

	//while ()
	ft_prompt();
	if (!isatty(0))
		ret = get_next_line(0, line);
	else
	{
		hist_init();
		ft_terminal(T_INIT);
		while (!(buf = 0)
				&& (ret = read(fd, &buf, 8)) > 0)
			if ((ret = ft_action(buf)) <= 0 || buf == K_RET)
				break ;
		ft_terminal(T_RESTORE);
		*line = line_tostr(&get_term()->cursor, ret == -1 ? 2 : 0);
		hist_commit(ret);
	}
	return (ret);
}
