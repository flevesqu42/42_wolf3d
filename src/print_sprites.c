/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 07:03:10 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:36:00 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_pointed_sprite(t_gen *gen)
{
	static clock_t	last_clock = 0;

	if ((gen->pointed_sprite)->inf.filter == 0xffffffff)
		last_clock = gen->clock;
	if (gen->clock - last_clock > 100)
		(gen->pointed_sprite)->inf.filter = 0xffffffff;
	if (!(gen->rep & GAME_MODE))
		(gen->pointed_sprite)->inf.filter = 0xff00ff00;
}

void	print_sprites_up(t_gen *g, t_sprite *c, int x, float *datas)
{
	while (datas[1] >= datas[3])
	{
		if (g->rep & (EDIT_SPRITE | GAME_MODE) && x == (g->screen->w >> 1)
				&& (int)datas[5] == (g->screen->h >> 1))
			g->pointed_sprite = c;
		datas[5] = g->screen->h - g->y_pos - datas[1];
		put_pixel_alpha(g->screen, x, datas[5]
			, lifemask(g, c->inf.filter & get_color_surface(datas[7]
				, 1.0 - (datas[6] + (datas[1] / datas[2]))
			, get_sprite(c->inf.rep, &g->medias))));
		--datas[1];
	}
}

void	print_sprites_down(t_gen *g, t_sprite *c, int x, float *datas)
{
	while (datas[0] >= datas[4])
	{
		if ((g->rep & (EDIT_SPRITE | GAME_MODE)) && x == (g->screen->w >> 1)
				&& (int)datas[5] == (g->screen->h >> 1))
			g->pointed_sprite = c;
		datas[5] = g->screen->h - g->y_pos + datas[0];
		put_pixel_alpha(g->screen, x, datas[5]
			, lifemask(g, c->inf.filter & get_color_surface(datas[7]
			, 1.0 - (datas[6] - (datas[0] / datas[2]))
			, get_sprite(c->inf.rep, &g->medias))));
		--datas[0];
	}
}

void	print_sprites(t_gen *g, t_sprite *c, int x, float a)
{
	float	datas[8];

	datas[6] = (g->tall - c->inf.height) / c->inf.tall;
	datas[2] = c->inf.size;
	datas[0] = datas[2] * datas[6];
	if ((datas[1] = datas[2] - datas[0]) > g->screen->h - g->y_pos)
		datas[1] = g->screen->h - g->y_pos;
	if ((datas[0] = datas[2] * datas[6]) > g->y_pos)
		datas[0] = g->y_pos;
	datas[3] = datas[2] - datas[0] - datas[2];
	datas[4] = datas[2] * datas[6] - datas[2];
	datas[7] = a;
	print_sprites_up(g, c, x, datas);
	print_sprites_down(g, c, x, datas);
}
