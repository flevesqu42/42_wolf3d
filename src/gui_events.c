/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 07:58:34 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 14:53:12 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	buttondown_event(SDL_Event *event, t_gen *gen)
{
	if (event->button.type == SDL_MOUSEBUTTONDOWN && !(gen->rep & MENU))
	{
		if (event->button.button == 3)
			gen->rep |= MOUSE_1;
		else if (event->button.button == 1)
			gen->rep |= MOUSE_2;
	}
}

static void	buttonup_event(SDL_Event *e, t_gen *gen)
{
	if (e->button.button == 1)
		gen->rep ^= MOUSE_2;
}

void		check_event(t_gen *gen, SDL_Event *e)
{
	if (e->type == SDL_QUIT)
		gen->rep ^= GUI_CONTINUE;
	if (e->motion.type == SDL_MOUSEMOTION)
	{
		if (gen->rep & MENU)
		{
			gen->mouse[0] = e->motion.x;
			gen->mouse[1] = e->motion.y;
		}
		else if (e->motion.y < gen->screen->h && e->motion.x < gen->screen->w)
		{
			gen->y_pos = e->motion.y;
			gen->pl.cam[2] = ANGLE(gen->pl.cam[2] + (M_PI / 1500
				* e->motion.xrel));
		}
	}
	if (e->key.type == SDL_KEYDOWN)
		keydown_event(e, gen);
	if (e->key.type == SDL_KEYUP)
		keyup_event(e, gen);
	buttondown_event(e, gen);
	if (e->button.type == SDL_MOUSEBUTTONUP)
		buttonup_event(e, gen);
}

void		gui_events(t_gen *gen)
{
	static SDL_Event	event;

	while (SDL_PollEvent(&event))
		check_event(gen, &event);
}
