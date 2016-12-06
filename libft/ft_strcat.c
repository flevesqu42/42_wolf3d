/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:13:14 by flevesqu          #+#    #+#             */
/*   Updated: 2016/06/01 06:10:56 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubc(char *s1, const char *s2, size_t *n)
{
	while (*s2)
	{
		s1[*n] = *s2;
		++*n;
		s2 += 1;
	}
	s1[*n] = '\0';
	return (s1);
}

char	*ft_strcat(char *s1, const char *s2)
{
	char	*ptr;

	ptr = s1;
	while (*ptr)
		ptr += 1;
	while (*s2)
	{
		*ptr = *s2;
		ptr += 1;
		s2 += 1;
	}
	*ptr = '\0';
	return (s1);
}
