/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/09 19:16:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

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
	if (buf == '\t')
		ft_autocomplit(get_term()->cursor);
	else if (buf == 127 && !line_bs(get_term()->cursor))
	{
		tputs(get_term()->cm_left, 1, term_print);
		tputs(tparm(get_term()->del_ch, 1), 1, term_print);
	}
	else if (buf == 0X445B1B && get_term()->cursor->prev)
	{
		tputs(get_term()->cm_left, 1, term_print);
		get_term()->cursor = get_term()->cursor->prev;
	}
	else if (buf == 0X435B1B && get_term()->cursor->next)
	{
		tputs(get_term()->cm_right, 1, term_print);
		get_term()->cursor = get_term()->cursor->next;
	}
	else if (buf == 0X415B1B || buf == 0X425B1B || buf == 0X435B1B
			|| buf == 0X445B1B)
		ft_dprintf(0, "\a");
	else if (buf != 127 && (buf > 31 || ft_iswhitespace(buf)))
	{
		tputs(get_term()->im_on, 1, term_print);
		ft_dprintf(0, "%s", &buf);
		line_add(get_term()->cursor, buf);
		tputs(get_term()->im_off, 1, term_print);
	}
}

int			ft_readline(const int fd, char **line)
{
	uint64_t		buf;

	ft_init_terminal(1);
	while (!(buf = 0) && read(fd, &buf, 8) > 0 && buf != 4)
		if (buf == '\n' && ft_dprintf(0, "\n"))
			break ;
		else
			ft_action(buf);
	ft_init_terminal(0);
	*line = line_tostr(&get_term()->cursor, 1);
	return (buf == '\n' ? 1 : 0);
}
