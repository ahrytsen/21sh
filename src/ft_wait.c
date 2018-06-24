/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 15:57:53 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/24 16:01:41 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

pid_t	ft_waitpid(pid_t pid, int *stat_loc, int options)
{
	pid_t	ret;

	while ((ret = waitpid(pid, stat_loc, options)) == -1)
		if (!ft_is_interrupted())
			break ;
	return (ret);
}
