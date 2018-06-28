/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:46:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/28 23:19:52 by ahrytsen         ###   ########.fr       */
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
	if (!get_environ()->proc)
	{
		ft_dprintf(2, "fg: no current job\n");
		return (1);
	}
	tmp = get_environ()->proc->next;
	get_environ()->pid = get_environ()->proc->content_size;
	free(get_environ()->proc);
	get_environ()->proc = tmp;
	kill(get_environ()->pid, SIGCONT);
	ft_waitpid(get_environ()->pid, &ret, WUNTRACED);
	get_environ()->pid = 0;
	ret = WEXITSTATUS(ret);
	return (ret);
}
