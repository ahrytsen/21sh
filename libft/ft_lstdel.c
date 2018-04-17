/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:05:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 17:51:36 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *buf;

	if (alst && del)
		while (*alst)
		{
			buf = (*alst)->next;
			(*del)((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = buf;
		}
}
