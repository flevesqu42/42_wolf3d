/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 07:51:34 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 14:56:59 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		increase_life(t_gen *gen)
{
	static clock_t	last_clock = 0;

	if (gen->pl.life < MAX_LIFE && gen->clock - last_clock >= 50)
	{
		gen->pl.life += 1;
		last_clock = gen->clock;
	}
}

void		loose_actions(t_gen *gen)
{
	static clock_t	last_clock = 0;

	if (gen->tall > 0.2 && gen->clock - last_clock >= 60)
	{
		gen->tall -= 0.02;
		last_clock = gen->clock;
	}
}

void		init_stat(t_gen *gen)
{
	static clock_t	last_clock = 0;
	static float	diff = 0;

	diff = ((float)gen->clock - (float)last_clock) / 1000.0;
	if ((gen->rep & (VICTORY | GAME_MODE)) == VICTORY)
		gen->rep ^= VICTORY;
	if (gen->pl.life && !(gen->rep & VICTORY))
	{
		if (gen->keys & 0x40)
			gen->tall = TALL_GIANT;
		else
			gen->tall = gen->keys & 0x20 ? TALL_ANT : TALL_NORMAL;
	}
	gen->run = gen->keys & 0x10 ? 4.0 : 6.0;
	gen->run *= gen->keys & 0x20 ? 2.0 : 1.0;
	gen->run /= diff * 20;
	if (!gen->run)
		gen->run = 4.0;
	if (gen->rep & EDIT_SPRITE)
		gen->pointed_sprite = NULL;
	last_clock = gen->clock;
}

void		game_mode_actions(t_gen *gen)
{
	if ((gen->pl.life && !(gen->rep & VICTORY)) || !(gen->rep & (GAME_MODE)))
	{
		strafes_actions(gen);
		move_actions(gen);
	}
	else if (!(gen->rep & VICTORY))
		loose_actions(gen);
	if (!(gen->rep & GAME_MODE))
	{
		mouse_actions_editor(gen);
		edit_sprite_actions(gen);
	}
	else
	{
		walked_sprite_action(gen);
		if (gen->pl.life)
		{
			increase_life(gen);
			mouse_actions_game(gen);
		}
	}
	init_sprites(gen);
	if (!gen->pointed_sprite)
		sort_sprites(gen);
}

void		game_loop(t_gen *gen)
{
	while (gen->rep & GUI_CONTINUE)
	{
		if (gen->screen != (gen->screen = SDL_GetWindowSurface(gen->win)))
			init_threads(gen);
		init_stat(gen);
		open_door(gen);
		if (!(gen->rep & MENU))
			game_mode_actions(gen);
		if (gen->pointed_sprite)
			set_pointed_sprite(gen);
		if (gen->rep & GAME_MODE)
			gen->pointed_sprite = NULL;
		go_threads(gen);
		gui_events(gen);
	}
}
