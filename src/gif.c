/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:22:12 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:29:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		open_door(t_gen *gen)
{
	static clock_t last_clock = 0;

	if (gen->rep & EDIT_SPRITE
		&& *gen->pointed_block && ((*gen->pointed_block & 0x0f) == 0x2
			|| ((*gen->pointed_block & 0xf) == 0x4
			&& gen->pl.keys & 0x1))
			&& gen->clock - last_clock >= 400)
	{
		if ((*gen->pointed_block & 0x70) == 0x50)
		{
			*gen->pointed_block = 0;
			gen->rep ^= EDIT_SPRITE;
		}
		else
			*gen->pointed_block = (*gen->pointed_block & 0x8f)
				| ((((*gen->pointed_block & 0x70) >> 4) + 1) << 4);
		last_clock = gen->clock;
	}
}
