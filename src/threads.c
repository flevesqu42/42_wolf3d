/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:33:01 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:55:28 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	push_commentary(t_gen *gen)
{
	static clock_t	last_clock = 0;

	if (gen->clock - last_clock > 3000)
		gen->commentary = NULL;
	if (!gen->commentary)
		last_clock = gen->clock;
	else if (gen->commentary)
	{
		put_square(gen
			, (int[2]){(gen->screen->w >> 3)
			, gen->screen->h - ((gen->screen->h >> 3))}
			, (int[2]){gen->screen->w - ((gen->screen->w >> 3))
			, gen->screen->h - (gen->screen->h >> 4)}, 0x50a0a0a0);
		push_text(gen->commentary, gen
			, (int[2]){(gen->screen->w >> 1)
				- ((ft_strlen(gen->commentary) >> 1) * 11)
			, gen->screen->h - (gen->screen->h >> 3) + 25}
			, COLOR_ORANGE);
	}
}

static void	preupdate_actions(t_gen *gen)
{
	text_actions(gen);
	push_commentary(gen);
	if (*gen->pointed_block == 0x84)
		gen->commentary = "There is a strange symbol here... why ?";
	if (gen->rep & MENU)
		integrate_menu(gen);
	else
	{
		if (gen->rep & SHOOT)
			set_surface(gen->screen, gen->medias.shoot
				, (gen->screen->w >> 1) - 25, (gen->screen->h >> 1) - 25);
		else if (gen->pl.life && !(gen->rep & VICTORY))
			print_cursor(gen->screen, (gen->screen->w >> 1)
				, (gen->screen->h >> 1));
	}
}

void		decrease_life(t_gen *gen, float decrease)
{
	static clock_t	last_clock = 0;

	if (gen->clock - last_clock >= 60)
	{
		decrease /= gen->screen->w >> 4;
		gen->pl.life -= decrease > gen->pl.life ? gen->pl.life : decrease;
		last_clock = gen->clock;
	}
}

void		go_threads(t_gen *gen)
{
	int				index[2];
	float			decrease;

	index[0] = 0;
	decrease = 0;
	while (index[0] < MT)
	{
		pthread_create(&gen->mt[index[0]].thread, NULL, graphical_events
			, &gen->mt[index[0]]);
		++index[0];
	}
	index[1] = 0;
	while (index[1] < MT)
	{
		pthread_join(gen->mt[index[1]].thread, NULL);
		decrease += gen->mt[index[1]].decrease;
		++index[1];
	}
	if (decrease)
		decrease_life(gen, decrease);
	preupdate_actions(gen);
	if (SDL_UpdateWindowSurface(gen->win) < 0)
		error(GUI_ERROR);
}
