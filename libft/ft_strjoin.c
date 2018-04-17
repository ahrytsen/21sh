/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:47:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/22 17:20:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	len;
	char	*new_string;

	j = 0;
	len = 0;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	if (!(new_string = ft_strnew(len)))
		return (NULL);
	while (s1 && *s1)
		new_string[j++] = *s1++;
	while (s2 && *s2)
		new_string[j++] = *s2++;
	new_string[j] = 0;
	return (new_string);
}
