/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:50:26 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/06 07:39:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n)
	{
		while (n - 1 && *((unsigned char *)s1) == *((unsigned char *)s2))
		{
			s1 += 1;
			s2 += 1;
			n--;
		}
		return (*(unsigned char *)(s1) - *((unsigned char *)s2));
	}
	else
		return (0);
}
