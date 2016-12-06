/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 05:47:14 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:28:59 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	keyup_setwalltypes(SDL_Event *event, t_gen *gen)
{
	if (event->key.keysym.scancode == 89)
		gen->wall_type = 0x1;
	else if (event->key.keysym.scancode == 90)
		gen->wall_type = 0x2;
	else if (event->key.keysym.scancode == 91)
		gen->wall_type = 0x3;
	else if (event->key.keysym.scancode == 92)
		gen->wall_type = 0x4;
	else if (event->key.keysym.scancode == 93)
		gen->wall_type = 0x5;
	else if (event->key.keysym.scancode == 94)
		gen->wall_type = 0x6;
}

static void	keyup_move(SDL_Event *event, t_gen *gen)
{
	if (event->key.keysym.scancode == 7
			|| event->key.keysym.scancode == 79)
		gen->keys ^= 0x1;
	else if (event->key.keysym.scancode == 4
			|| event->key.keysym.scancode == 80)
		gen->keys ^= 0x2;
	else if (event->key.keysym.scancode == 26
			|| event->key.keysym.scancode == 82)
		gen->keys ^= 0x4;
	else if (event->key.keysym.scancode == 22
			|| event->key.keysym.scancode == 81)
		gen->keys ^= 0x8;
}

void		keyup_event(SDL_Event *event, t_gen *gen)
{
	if (event->key.keysym.scancode == 44
			&& (gen->pl.life == 0 || (gen->rep & VICTORY)))
		new_game(gen, gen->file, gen->file);
	if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		gen->keys ^= 0x10;
	else if (event->key.keysym.scancode == SDL_SCANCODE_LGUI)
		gen->keys ^= 0x20;
	else if (event->key.keysym.scancode == 8 && gen->rep & EDIT_SPRITE)
		gen->rep ^= EDIT_SPRITE;
	else if (event->key.keysym.scancode == 44)
		gen->keys ^= 0x40;
	else if (event->key.keysym.scancode == 87)
		gen->keys ^= 0x80;
	else if (event->key.keysym.scancode == 86)
		gen->keys ^= 0x100;
	else if (event->key.keysym.scancode == 45)
		gen->keys ^= 0x200;
	else if (event->key.keysym.scancode == 46)
		gen->keys ^= 0x400;
	else
	{
		keyup_move(event, gen);
		keyup_setwalltypes(event, gen);
	}
}
