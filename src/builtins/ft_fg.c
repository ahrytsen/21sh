/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:46:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/29 22:37:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int			ft_count_fg(t_list *proc)
{
	if (!proc)
		return (0);
	return (ft_count_fg(proc->next) + 1);
}

int			ft_fg(char **av)
{
	t_list	*tmp;
	int		ret;

	(void)av;
	if (!get_environ()->jobs)
	{
		ft_dprintf(2, "fg: no current job\n");
		return (1);
	}
	tmp = get_environ()->jobs->next;
	get_environ()->pid = get_environ()->jobs->content_size;
	free(get_environ()->jobs);
	get_environ()->jobs = tmp;
	kill(get_environ()->pid, SIGCONT);
	ret = ft_control_job_fg();
	get_environ()->pid = 0;
	return (ft_status_job(ret));
}
