/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:17:11 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:32:58 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	set_sprites_actions(t_gen *gen)
{
	if (gen->rep & SET_COIN)
	{
		new_sprite(&gen->sprites, 2, gen);
		gen->rep ^= SET_COIN;
	}
	if (gen->rep & SET_SMITH)
	{
		new_sprite(&gen->sprites, 1, gen);
		gen->rep ^= SET_SMITH;
	}
	if (gen->rep & SET_MUN)
	{
		new_sprite(&gen->sprites, 3, gen);
		gen->rep ^= SET_MUN;
	}
	if (gen->rep & SET_BOSS)
	{
		new_sprite(&gen->sprites, 4, gen);
		gen->rep ^= SET_BOSS;
	}
	if (gen->rep & SET_KEY)
	{
		new_sprite(&gen->sprites, 5, gen);
		gen->rep ^= SET_KEY;
	}
}

void		mouse_actions_editor(t_gen *gen)
{
	if (!gen->pointed_sprite)
	{
		if (gen->pointed_block
				!= &gen->map[(int)gen->pl.cam[1]][(int)gen->pl.cam[0]]
				&& gen->blocks_counter && gen->rep & MOUSE_2
				&& !(*gen->pointed_block & (0x8f)))
		{
			*gen->pointed_block |= gen->wall_type;
			--gen->blocks_counter;
		}
		else if (gen->rep & MOUSE_1 && (*gen->pointed_block & (0xf)))
		{
			*gen->pointed_block &= 0x80;
			gen->rep ^= MOUSE_1;
			++gen->blocks_counter;
		}
	}
	else if (gen->rep & MOUSE_2 && gen->pointed_sprite)
	{
		gen->pointed_sprite->inf.x = gen->pointed_coord[0];
		gen->pointed_sprite->inf.y = gen->pointed_coord[1];
	}
	else if (gen->rep & MOUSE_1 && gen->pointed_sprite)
		delete_sprite(gen, gen->pointed_sprite);
	set_sprites_actions(gen);
}

void		mouse_actions_game(t_gen *gen)
{
	static clock_t	last_time = 0;

	if (gen->clock - last_time < 100)
		gen->rep |= SHOOT;
	else if (gen->rep & SHOOT)
		gen->rep ^= SHOOT;
	if (gen->rep & (MOUSE_2 | MOUSE_2) && gen->pl.munitions
		&& gen->clock - last_time >= 250)
	{
		--gen->pl.munitions;
		if (gen->pointed_sprite && gen->pl.munitions
				&& ((gen->pointed_sprite->inf.rep & 0xff) == 1
				|| (gen->pointed_sprite->inf.rep & 0xff) == 4))
		{
			gen->pointed_sprite->inf.filter = 0xffff0000;
			gen->pointed_sprite->inf.rep =
				(gen->pointed_sprite->inf.rep & 0xff)
				| ((((gen->pointed_sprite->inf.rep & 0xff00) >> 8) - 1) << 8);
			if (!(gen->pointed_sprite->inf.rep & 0xff00))
				gen->pointed_sprite->inf.rep |= S_HIDE;
			if ((gen->pointed_sprite->inf.rep & 0xff) == 0x84)
				gen->rep |= VICTORY;
		}
		last_time = gen->clock;
	}
}
