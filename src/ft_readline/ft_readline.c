/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/12 15:43:27 by ahrytsen         ###   ########.fr       */
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

static void	ft_action(uint64_t buf)
{
	if (buf == K_TAB)
		ft_autocomplit(get_term()->cursor);
	else if (buf == K_BS)
		ft_back_space();
	else if (buf == K_AUP || buf == K_ADOWN || buf == K_RIGHT || buf == K_LEFT
			|| buf == K_HOME || buf == K_END)
		ft_move(buf);
	else if (buf == K_ALEFT || buf == K_ARIGHT || buf == K_ABS || buf == K_ADEL)
		ft_word_action(buf);
	else
		ft_add(buf);
}

int			ft_readline(const int fd, char **line)
{
	uint64_t		buf;

	ft_terminal(T_INIT);
	while (!(buf = 0) && read(fd, &buf, 8) > 0)
		if (buf == K_RET)
		{
			while (get_term()->cursor->next
				&& (get_term()->cursor = get_term()->cursor->next))
				ft_curright(1);
			ft_dprintf(0, "\n");
			break ;
		}
		else if (buf == 4)
		{
			if (ft_del())
				break ;
		}
		else
			ft_action(buf);
	ft_terminal(T_RESTORE);
	*line = line_tostr(&get_term()->cursor, 1);
	return (buf == '\n' ? 1 : 0);
}
