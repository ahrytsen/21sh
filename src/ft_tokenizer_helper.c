/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:25:13 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/06 17:14:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_isseparator(int c)
{
	return (ft_strchr("|&;()<> \t\n", c) ? 1 : 0);
}

int		ft_is_fd(t_token *tok, int mod)
{
	char	*tmp;

	tmp = tok->data.word;
	while (*tmp)
		if (!ft_isdigit(*tmp++))
			return (0);
	return (1);
}
