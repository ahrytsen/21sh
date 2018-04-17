/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_splitwhitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:41:25 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/13 14:18:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		ft_skip_slash(char **s)
{
	if (*++(*s))
		(*s)++;
}

static void		ft_skip_qoutes(char **s)
{
	char	q;

	q = *(*s)++;
	while (**s != q)
		if (!**s)
			quotes_error(q);
		else if (q == '"' && **s == '`')
			ft_skip_qoutes(s);
		else if (q != '\'' && **s == '\\' && (*s)++)
			**s ? (*s)++ : 0;
		else
			(*s)++;
	(*s)++;
}

static size_t	ft_countcmd(char *s)
{
	int		m;
	size_t	res;

	m = 0;
	res = 0;
	while (*s)
		if (*s == '"' || *s == '\'' || *s == '`' || *s == '\\')
		{
			!m ? (res++) : 0;
			m = 1;
			(*s == '\\') ? ft_skip_slash(&s) : ft_skip_qoutes(&s);
		}
		else if (!ft_iswhitespace(*s) && s++ && !m)
		{
			m = 1;
			res++;
		}
		else if (ft_iswhitespace(*s) && s++)
			m = 0;
	return (res);
}

static void		*ft_freesplit(char **split, size_t i)
{
	while (i--)
		free(split[i]);
	free(split);
	return (NULL);
}

char			**msh_splitwhitespaces(char *line)
{
	size_t	i;
	char	**split;
	char	*st;
	int		m;

	i = 0;
	m = 0;
	if (!line ||
		!(split = (char**)ft_memalloc((ft_countcmd(line) + 1) * sizeof(char*))))
		return (NULL);
	while (*line)
		if ((*line == '"' || *line == '\'' || *line == '`' || *line == '\\')
			&& (!m ? (int)(st = line) : 1) && ++m)
			*line == '\\' ? ft_skip_slash(&line) : ft_skip_qoutes(&line);
		else if (!ft_iswhitespace(*line) && line++ && !m && (m = 1))
			st = line - 1;
		else if (ft_iswhitespace(*line) && line++ && m && !(m = 0))
			if (!(split[i++] = parse_argv(ft_strsub(st, 0, line - st - 1))))
				return (ft_freesplit(split, --i));
	return ((m && !(split[i] = parse_argv(ft_strsub(st, 0, line - st))))
			? ft_freesplit(split, i) : split);
}
