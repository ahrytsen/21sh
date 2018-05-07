/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:27:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/07 17:01:53 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <21sh.h>
# include <termios.h>
# include <term.h>

/*
**				ft_readline/ft_readline.c
*/
int				ft_readline(char **line);
/*
**				ft_readline/line.c
*/
char			*line_tostr(t_cmdline *cmdline, int mod);
int				line_bs(t_cmdline *cmdline);
int				line_add(t_cmdline *cmdline, uint64_t buf);
int				line_addch(t_cmdline *cmdline, char ch);
void			line_free(t_cmdline *cmdline);
/*
**				ft_readline/ft_autocomplit.c
*/
void			ft_autocomplit(t_cmdline *cursor);

#endif
