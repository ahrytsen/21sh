/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:37:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/25 15:43:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	ft_toread_prompt(int mod)
{
	int			tmp;
	const char	*prompt;

	if (mod == P_QUOTE)
		prompt = "quote > ";
	else if (mod == P_BQUOTE)
		prompt = "bquote > ";
	else if (mod == P_DQUOTE)
		prompt = "dquote > ";
	else if (mod == P_HEREDOC)
		prompt = "heredoc > ";
	else if (mod == P_BSLASH)
		prompt = "bslash > ";
	tmp = ft_strlen(prompt);
	get_term()->cury = tmp / get_term()->width;
	get_term()->curx = tmp % get_term()->width;
	ft_dprintf(2, "\r%s\033[31m%s\033[0m",
				tgetstr("cd", NULL), prompt);
}

static void	ft_user_prompt(void)
{
	int		tmp;
	char	pwd[MAXPATHLEN];

	getcwd(pwd, MAXPATHLEN);
	tmp = ft_strlen(pwd) + 4;
	get_term()->cury = tmp / get_term()->width;
	get_term()->curx = tmp % get_term()->width;
	ft_dprintf(2, "\r%s\033[33m%s \033[32m$>\033[0m ",
				tgetstr("cd", NULL), pwd);
}

void		ft_prompt(void)
{
	if (isatty(2))
	{
		ft_user_prompt();
	}
	else
		ft_toread_prompt(P_BQUOTE);
}
