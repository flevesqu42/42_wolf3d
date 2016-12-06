/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:24:24 by flevesqu          #+#    #+#             */
/*   Updated: 2016/06/07 06:23:06 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*s)
	{
		if (*s == (char)c)
			tmp = (char*)s;
		s += 1;
		if (*s == (char)c)
			tmp = (char*)s;
	}
	return (tmp);
}

char	*ft_ifstrrchr(char *s, int c)
{
	char	*tmp;
	char	*first;

	first = s;
	tmp = NULL;
	while (*s)
	{
		if (*s == (char)c)
			tmp = (char*)s;
		s += 1;
		if (*s == (char)c)
			tmp = (char*)s;
	}
	return (tmp ? tmp : first);
}
