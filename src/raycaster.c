/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 07:53:40 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:36:01 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float			cast_ray_hor(float *coord, float *ray, t_thread *thread
	, t_gen *gen)
{
	if (coord[0] < 0 || coord[0] > gen->x_max + 1
			|| coord[1] < 1 || coord[1] > gen->y_max + 1)
		return (-1);
	while (!(gen->map[(int)(ray[1] < 0 ? coord[1] - 1
		: coord[1])][(int)(coord[0])]))
	{
		coord[0] += ray[0];
		coord[1] += ray[1];
		if (coord[0] < 0 || coord[0] > gen->x_max + 1
				|| coord[1] < 0 || coord[1] > gen->y_max + 1)
			return (-1);
	}
	thread->coords_hor[0] = coord[0];
	thread->coords_hor[1] = coord[1];
	return (sqrtf((gen->pl.cam[1] - coord[1]) * (gen->pl.cam[1] - coord[1])
		+ ((gen->pl.cam[0] - coord[0]) * (gen->pl.cam[0] - coord[0]))));
}

static float	cast_ray_ver(float *coord, float *ray, t_thread *thread
	, t_gen *gen)
{
	if (coord[0] < 1 || coord[0] > gen->x_max + 1
			|| coord[1] < 0 || coord[1] > gen->y_max + 1)
		return (-1);
	while (!(gen->map[(int)(coord[1])][(int)(ray[0] < 0 ? coord[0] - 1
		: coord[0])]))
	{
		coord[0] += ray[0];
		coord[1] += ray[1];
		if (coord[0] < 0 || coord[0] > gen->x_max + 1
				|| coord[1] < 0 || coord[1] > gen->y_max + 1)
			return (-1);
	}
	thread->coords_ver[0] = coord[0];
	thread->coords_ver[1] = coord[1];
	return (sqrtf(((gen->pl.cam[1] - coord[1]) * (gen->pl.cam[1] - coord[1]))
		+ ((gen->pl.cam[0] - coord[0]) * (gen->pl.cam[0] - coord[0]))));
}

static void		get_pointed_cell(t_thread *t, t_gen *g)
{
	if (t->rep & WALL_HORIZONTAL)
	{
		t->cell = &g->map[(int)(t->dir[1] < 0 ? (int)t->coords_hor[1] - 1
			: (int)t->coords_hor[1])][(int)t->coords_hor[0]];
		if (t->x == (g->screen->w >> 1))
		{
			g->pointed_block = t->cell;
			g->pointed_coord[0] = t->coords_hor[0];
			g->pointed_coord[1] = t->dir[1] < 0 ? t->coords_hor[1] - 1
				: t->coords_hor[1];
		}
	}
	else
	{
		t->cell = &g->map[(int)t->coords_ver[1]][(int)(t->dir[0] < 0
			? (int)t->coords_ver[0] - 1 : (int)t->coords_ver[0])];
		if (t->x == (g->screen->w >> 1))
		{
			g->pointed_block = t->cell;
			g->pointed_coord[0] = t->dir[0] < 0 ? t->coords_ver[0] - 1
				: t->coords_ver[0];
			g->pointed_coord[1] = t->coords_ver[1];
		}
	}
}

static float	get_obstacle(float a, t_thread *t, t_gen *gen)
{
	float	coord[2];
	float	ray[2];

	t->dir[0] = cosf(a) > 0 ? +1 : -1;
	t->dir[1] = sinf(a) > 0 ? +1 : -1;
	coord[0] = t->dir[0] > 0 ? (int)(gen->pl.cam[0] + t->dir[0])
		: (int)gen->pl.cam[0];
	coord[1] = gen->pl.cam[1] + VER(a, (coord[0] - gen->pl.cam[0]), t->dir[1]);
	ray[0] = t->dir[0];
	ray[1] = VER(a, 1, t->dir[1]);
	t->dist[1] = cast_ray_ver(coord, ray, t, gen);
	coord[1] = t->dir[1] > 0 ? (int)(gen->pl.cam[1] + t->dir[1])
		: (int)gen->pl.cam[1];
	coord[0] = gen->pl.cam[0] + HOR(a, (coord[1] - gen->pl.cam[1]), t->dir[0]);
	ray[1] = t->dir[1];
	ray[0] = HOR(a, 1, t->dir[0]);
	t->dist[0] = cast_ray_hor(coord, ray, t, gen);
	if (t->dist[0] != -1 && (t->dist[0] < t->dist[1] || t->dist[1] == -1))
		t->rep |= WALL_HORIZONTAL;
	else if (t->rep & WALL_HORIZONTAL)
		t->rep ^= WALL_HORIZONTAL;
	get_pointed_cell(t, gen);
	return (t->rep & WALL_HORIZONTAL ? DIST_FINAL(t->dist[0])
		: DIST_FINAL(t->dist[1]));
}

void			get_distance(float a, t_thread *thread, t_gen *gen, float *dist)
{
	dist[2] = get_obstacle(a, thread, gen);
	dist[0] = (dist[2] * gen->tall);
	if ((dist[1] = dist[2] - dist[0] - 1) > gen->screen->h - gen->y_pos)
		dist[1] = gen->screen->h - gen->y_pos;
	if ((dist[0] = (dist[2] * gen->tall)) > gen->y_pos)
		dist[0] = gen->y_pos;
	if (thread->rep & WALL_HORIZONTAL)
	{
		thread->coords_final = thread->coords_hor;
		thread->dist[2] = thread->dist[0];
	}
	else
	{
		thread->coords_final = thread->coords_ver;
		thread->dist[2] = thread->dist[1];
	}
}
