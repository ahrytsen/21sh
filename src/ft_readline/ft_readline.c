/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/11 21:05:51 by ahrytsen         ###   ########.fr       */
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
	if (buf == '\t')
		ft_autocomplit(get_term()->cursor);
	else if (buf == 127)
		ft_back_space();
	else if (buf == 0X415B1B || buf == 0X425B1B || buf == 0X435B1B
			|| buf == 0X445B1B)
		ft_move(buf);
	else
		ft_add(buf);
}

int			ft_readline(const int fd, char **line)
{
	uint64_t		buf;

	ft_init_terminal(1);
	while (!(buf = 0) && read(fd, &buf, 8) > 0)
		if (buf == '\n')
		{
			while (get_term()->cursor->next)
			{
				get_term()->cursor = get_term()->cursor->next;
				ft_curright(1);
			}
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
	ft_init_terminal(0);
	*line = line_tostr(&get_term()->cursor, 1);
	return (buf == '\n' ? 1 : 0);
}
