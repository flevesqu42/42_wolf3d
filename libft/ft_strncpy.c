/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:53:24 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/12 07:55:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if (src[index] == '\0')
			while (index < n)
			{
				dst[index] = '\0';
				index++;
			}
		else
		{
			dst[index] = src[index];
			index++;
		}
	}
	return (dst);
}
