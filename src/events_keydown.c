/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keydown.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 05:47:30 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:28:58 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	keydown_rep(SDL_Event *event, t_gen *gen)
{
	if (event->key.keysym.scancode == 20)
		gen->rep ^= MENU;
	else if (event->key.keysym.scancode == 41)
		gen->rep ^= GUI_CONTINUE;
	else if (event->key.keysym.scancode == 8)
		gen->rep |= EDIT_SPRITE;
	else if (event->key.keysym.scancode == 6)
		gen->rep |= SET_COIN;
	else if (event->key.keysym.scancode == 25)
		gen->rep |= SET_SMITH;
	else if (event->key.keysym.scancode == 9)
		gen->rep |= SET_MUN;
	else if (event->key.keysym.scancode == 21)
		gen->rep |= SET_BOSS;
	else if (event->key.keysym.scancode == 23)
		gen->rep |= SET_KEY;
}

static void	keydown_move(SDL_Event *event, t_gen *gen)
{
	if (event->key.keysym.scancode == 7
			|| event->key.keysym.scancode == 79)
		gen->keys |= 0x1;
	else if (event->key.keysym.scancode == 4
			|| event->key.keysym.scancode == 80)
		gen->keys |= 0x2;
	else if (event->key.keysym.scancode == 26
			|| event->key.keysym.scancode == 82)
		gen->keys |= 0x4;
	else if (event->key.keysym.scancode == 22
			|| event->key.keysym.scancode == 81)
		gen->keys |= 0x8;
}

void		keydown_event(SDL_Event *event, t_gen *gen)
{
	keydown_rep(event, gen);
	keydown_move(event, gen);
	if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		gen->keys |= 0x10;
	else if (event->key.keysym.scancode == SDL_SCANCODE_LGUI)
		gen->keys |= 0x20;
	else if (event->key.keysym.scancode == 44)
		gen->keys |= 0x40;
	else if (event->key.keysym.scancode == 87)
		gen->keys |= 0x80;
	else if (event->key.keysym.scancode == 86)
		gen->keys |= 0x100;
	else if (event->key.keysym.scancode == 45)
		gen->keys |= 0x200;
	else if (event->key.keysym.scancode == 46)
		gen->keys |= 0x400;
}
