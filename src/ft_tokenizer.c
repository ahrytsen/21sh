/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:35:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/31 19:22:23 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_token	*ft_get_token(char **ln)
{
	int	f;

	f = 0;
	while (**ln && (!ft_iswhitespace(**ln) || !f))
	{

	}
}

int	ft_tokenizer(char *ln, t_token **t)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while(*ln)
	{

	}
	return (i);
}
