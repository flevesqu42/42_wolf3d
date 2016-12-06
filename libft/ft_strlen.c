/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:46:37 by flevesqu          #+#    #+#             */
/*   Updated: 2016/06/01 10:21:18 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t	ft_unsignlen(size_t i)
{
	size_t	value;

	value = 0;
	if (!i)
		value = 1;
	while (i)
	{
		++value;
		i /= 10;
	}
	return (value);
}

size_t	ft_strlen(const char *str)
{
	size_t	value;

	value = 0;
	while (str[value])
		value++;
	return (value);
}
