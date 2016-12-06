/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 05:46:43 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:29:08 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	set_sky(int x, float y_origin, float a, t_gen *gen)
{
	a /= TAU;
	while (y_origin > 0)
	{
		put_pixel(gen->screen, x, y_origin
			, lifemask(gen, get_color_surface(a, (gen->y_pos + y_origin)
				* (0.5 / gen->screen->h), gen->medias.sky)));
		--y_origin;
	}
}

static void	set_ceil(int x, float y, t_thread *thread, t_gen *gen)
{
	float	coord[2];
	float	diff[2];
	float	dist;

	coord[0] = thread->coords_final[0];
	coord[1] = thread->coords_final[1];
	while (y >= 0)
	{
		diff[0] = coord[0] - gen->pl.cam[0];
		diff[1] = coord[1] - gen->pl.cam[1];
		dist = (gen->cnst / sqrt((diff[1] * diff[1]) + (diff[0] * diff[0])))
			* (1.0 - gen->tall);
		coord[0] -= diff[0] / dist;
		coord[1] -= diff[1] / dist;
		put_pixel_alpha(gen->screen, x, y
			, lifemask(gen, get_color_surface(coord[0] - (int)coord[0]
			, coord[1] - (int)coord[1], gen->medias.ceil)));
		--y;
	}
}

static void	set_floor(int x, int y, t_thread *thread, t_gen *gen)
{
	float	coord[2];
	float	diff[2];
	float	dist;

	coord[0] = thread->coords_final[0];
	coord[1] = thread->coords_final[1];
	while (y < gen->screen->h)
	{
		diff[0] = coord[0] - gen->pl.cam[0];
		diff[1] = coord[1] - gen->pl.cam[1];
		dist = (gen->cnst / sqrt((diff[1] * diff[1]) + (diff[0] * diff[0])))
			* gen->tall;
		coord[0] -= diff[0] / dist;
		coord[1] -= diff[1] / dist;
		put_pixel_alpha(gen->screen, x, y
			, lifemask(gen, get_color_surface(coord[0] - (int)coord[0]
			, coord[1] - (int)coord[1], gen->medias.floor)));
		if (x == (gen->screen->w >> 1) && y == (gen->screen->h >> 1))
		{
			gen->pointed_block = &gen->map[(int)coord[1]][(int)coord[0]];
			gen->pointed_coord[0] = coord[0];
			gen->pointed_coord[1] = coord[1];
		}
		++y;
	}
}

static void	print_wall(float *dist, int x, t_thread *thread, t_gen *gen)
{
	thread->coord_wall = thread->rep & WALL_HORIZONTAL
		? thread->coords_final[0] - (int)thread->coords_final[0]
		: thread->coords_final[1] - (int)thread->coords_final[1];
	while (dist[1] >= 0)
	{
		put_pixel_alpha(gen->screen, x, gen->screen->h - gen->y_pos - dist[1]
			, lifemask(gen, get_shadow(get_color_surface(thread->coord_wall
				, 1.0 - (gen->tall + (dist[1] / dist[2]))
				, get_surface(*thread->cell, &gen->medias))
				, thread->rep & WALL_HORIZONTAL)));
		--dist[1];
	}
	while (dist[0] >= 0)
	{
		put_pixel_alpha(gen->screen, x, gen->screen->h - gen->y_pos + dist[0]
			, lifemask(gen, get_shadow(get_color_surface(thread->coord_wall
				, 1.0 - (gen->tall - (dist[0] / dist[2]))
				, get_surface(*thread->cell, &gen->medias))
				, thread->rep & WALL_HORIZONTAL)));
		--dist[0];
	}
}

void		*graphical_events(void *t)
{
	float		a;
	float		dist[3];
	t_thread	*thr;
	t_gen		*gen;

	thr = (t_thread*)t;
	thr->decrease = 0;
	gen = thr->gen;
	thr->x = thr->x_min;
	a = ANGLE(A_LESS(gen->pl.cam[2] + thr->a));
	while (thr->x < thr->x_max)
	{
		get_distance(a, thr, gen, dist);
		set_sky(thr->x, gen->screen->h - gen->y_pos + dist[0], a, gen);
		set_ceil(thr->x, gen->screen->h - gen->y_pos - dist[1], thr, gen);
		set_floor(thr->x, gen->screen->h - gen->y_pos + dist[0], thr, gen);
		print_wall(dist, thr->x, thr, gen);
		set_sprites(gen, thr, a);
		a = ANGLE(a + A_DIST);
		++thr->x;
	}
	return (NULL);
}
