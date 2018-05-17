/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/17 21:21:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

t_term		*get_term(void)
{
	static t_term	term;

	return (&term);
}

int			term_print(int c)
{
	return (write(0, &c, 1));
}

static int	ft_action(uint64_t buf)
{
	if (buf == K_RET)
		buf = ft_readline_ret();
	else if (buf == 4)
		buf = ft_del();
	else if (buf == K_TAB)
		ft_autocomplit(get_term()->cursor);
	else if (buf == K_BS)
		ft_back_space();
	else if (buf == K_AUP || buf == K_ADOWN || buf == K_RIGHT || buf == K_LEFT
			|| buf == K_HOME || buf == K_END)
		ft_move(buf);
	else if (buf == K_ALEFT || buf == K_ARIGHT || buf == K_ABS || buf == K_ADEL)
		ft_word_action(buf);
	else if (buf == K_UP || buf == K_DOWN)
		hist_move(buf);
	else if (buf  == K_SLEFT || buf == K_SUP || buf == K_ASLEFT
			|| buf == K_SRIGHT || buf == K_SDOWN || buf == K_ASRIGHT)
		ft_highlight(buf);
	else if (((char*)&buf)[0] != 27)
		buf = ft_add(buf);
	else
		ft_dprintf(0, "\a");
	ft_highlight_helper(buf);
	return (buf);
}

int			ft_readline(const int fd, char **line)
{
	int				ret;
	uint64_t		buf;

	hist_init();
	ft_terminal(T_INIT);
	while (!(buf = 0)
			&& (ret = read(fd, &buf, 8)) > 0)
		if ((ret = ft_action(buf)) <= 0 || buf == K_RET)
			break ;
	ft_terminal(T_RESTORE);
	*line = line_tostr(&get_term()->cursor, ret == -1 ? 2 : 0);
	hist_commit(ret);
	return (ret);
}
