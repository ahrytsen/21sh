/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:35:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/16 21:59:57 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		cmdline_addch(t_cmdline *cmdline, char ch)
{
	t_cmdline	*new_ch;
	t_cmdline	*tmp;

	if (!cmdline || !(new_ch = ft_memalloc(sizeof(*new_ch))))
		return (-1);
	new_ch->ch = ch;
	tmp = cmdline->prev;
	cmdline->prev = new_ch;
	new_ch->next = cmdline;
	new_ch->prev = tmp;
	if (tmp)
		tmp->next = new_ch;
	return (0);
}

int		cmdline_add(t_cmdline *cmdline, uint64_t buf)
{
	char	buf_ch[9];
	int		i;

	i = 0;
	ft_bzero(buf_ch, 9);
	ft_memcpy(buf_ch, &buf, 8);
	while (buf_ch[i])
		if (cmdline_addch(cmdline, buf_ch[i++]) == -1)
			return (-1);
	return (0);
}

int		cmdline_bs(t_cmdline *cmdline)
{
	t_cmdline	*tmp;

	if (!cmdline || !cmdline->prev)
		return (-1);
	tmp = cmdline->prev->prev;
	free(cmdline->prev);
	tmp ? tmp->next = cmdline : 0;
	cmdline->prev = tmp;
	return (0);
}

char	*cmdline_tostr(t_cmdline *cmdline, int mod)
{
	size_t		size;
	char		*line;
	t_cmdline	*tmp;
	size_t		i;

	if (!cmdline)
		return (NULL);
	size = 1;
	i = 0;
	while (cmdline->prev && size++)
		cmdline = cmdline->prev;
	if (!(line = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	while (cmdline->ch)
	{
		tmp = cmdline;
		line[i++] = cmdline->ch;
		cmdline = cmdline->next;
		mod ? free(tmp) : 0;
		mod ? cmdline->prev = NULL : 0;
	}
	mod == 2 ? ft_memdel((void*)line) : 0;
	return (line);
}

void	cmdline_free(t_cmdline *cmdline)
{
	t_cmdline	*tmp;
	t_cmdline	*tmp1;

	tmp = cmdline;
	if (!cmdline)
		return ;
	cmdline = cmdline->prev;
	while (cmdline)
	{
		tmp1 = cmdline;
		cmdline = cmdline->prev;
		free(tmp1);
	}
	tmp->prev = NULL;
}
