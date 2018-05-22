/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:37:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/22 15:05:42 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*static void	ft_toread_prompt(void)
{

}*/

static void	ft_user_prompt()
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

void	ft_prompt(void)
{
	if (isatty(2))
	{
		ft_user_prompt();
	}
}
