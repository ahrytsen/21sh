/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/05 19:30:39 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

int			term_print(int c)
{
	return (write(0, &c, 1));
}

static int	ft_action(uint64_t buf)
{
	if (buf == '\n' && ft_dprintf(0, "\n"))
		return (1);
	else if (buf == '\t')
		ft_autocomplit(msh_get_environ()->cursor);
	else if (buf == 127 && !cmdline_bs(msh_get_environ()->cursor))
	{
		tputs(msh_get_environ()->cm_left, 1, term_print);
		tputs(tparm(msh_get_environ()->del_ch, 1), 1, term_print);
	}
	else if (buf == 0X445B1B && msh_get_environ()->cursor->prev)
	{
		tputs(msh_get_environ()->cm_left, 1, term_print);
		msh_get_environ()->cursor = msh_get_environ()->cursor->prev;
	}
	else if (buf == 0X435B1B && msh_get_environ()->cursor->next)
	{
		tputs(msh_get_environ()->cm_right, 1, term_print);
		msh_get_environ()->cursor = msh_get_environ()->cursor->next;
	}
	else if (buf == 0X415B1B || buf == 0X425B1B || buf == 0X435B1B
			|| buf == 0X445B1B)
		ft_dprintf(0, "\a");
	else if (buf != 127 && (buf > 31 || ft_iswhitespace(buf)))
	{
		tputs(msh_get_environ()->im_on, 1, term_print);
		ft_dprintf(0, "%s", &buf);
		cmdline_add(msh_get_environ()->cursor, buf);
		tputs(msh_get_environ()->im_off, 1, term_print);
	}
	return (0);
}

int			ft_readline(char **line)
{
	uint64_t		buf;

	ft_init_terminal(1);
	while (!(buf = 0) && read(0, &buf, 8) > 0 && buf != 4)
		if (ft_action(buf))
			break ;
	ft_init_terminal(0);
	*line = cmdline_tostr(msh_get_environ()->cursor, 1);
	return (buf == '\n' ? 1 : 0);
}
