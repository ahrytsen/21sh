/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:56:32 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/11 20:17:53 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	slash(t_buf **cur, char **line)
{
	ft_putchar_mshbuf(cur, *(*line)++);
	**line ? ft_putchar_mshbuf(cur, *(*line)++) : 0;
}

static void	ft_dquote(t_buf **cur, char **line)
{
	while (**line != '"' && **line)
		if (**line == '\\')
			slash(cur, line);
		else
			ft_putchar_mshbuf(cur, *(*line)++);
	ft_putchar_mshbuf(cur, **line);
	**line ? (*line)++ : 0;
}

static void	ft_quote(t_buf **cur, char **line)
{
	char	*st;

	st = (*line)++;
	while (**line != '\'' && **line)
		(*line)++;
	ft_putstr_mshbuf(cur, st, *line - st + 1);
	**line ? (*line)++ : 0;
}

char		*parse_line(char *line)
{
	char	*tmp;
	t_buf	*head;
	t_buf	*cur;

	tmp = line;
	if (!(head = ft_memalloc(sizeof(t_buf))) || !line)
		ft_fatal(1, exit, "21sh: malloc error\n");
	cur = head;
	while (*line)
		if (*line == '\\')
			slash(&cur, &line);
		else if (*line == '\'')
			ft_quote(&cur, &line);
		else if (*line == '"')
			ft_dquote(&cur, &line);
		else if (*line == '`' && line++)
			ft_bquote(&cur, &line);
		else
			ft_putchar_mshbuf(&cur, *line++);
	free(tmp);
	return (ft_buftostr(head));
}
