/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:27:56 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:29:49 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	edit_sprite_actions(t_gen *gen)
{
	if (gen->keys & 0x80 && gen->pointed_sprite
			&& gen->pointed_sprite->inf.tall
			+ gen->pointed_sprite->inf.height < 1.0)
		gen->pointed_sprite->inf.tall += 0.01;
	if (gen->keys & 0x100 && gen->pointed_sprite
			&& gen->pointed_sprite->inf.tall > 0.02)
		gen->pointed_sprite->inf.tall -= 0.01;
	if (gen->keys & 0x200 && gen->pointed_sprite
			&& gen->pointed_sprite->inf.height > 0.0)
		gen->pointed_sprite->inf.height -= 0.01;
	if (gen->keys & 0x400 && gen->pointed_sprite
			&& gen->pointed_sprite->inf.height
			+ gen->pointed_sprite->inf.tall < 1.0)
		gen->pointed_sprite->inf.height += 0.01;
}

void	init_sprites(t_gen *g)
{
	t_sprite	*s;

	s = g->sprites;
	while (s)
	{
		if (!g->pointed_sprite)
			s->inf.filter = 0xffffffff;
		s->inf.dist = sqrtf(((g->pl.cam[0] - s->inf.x)
			* (g->pl.cam[0] - s->inf.x))
			+ ((g->pl.cam[1] - s->inf.y)
			* (g->pl.cam[1] - s->inf.y)));
		if ((s->inf.x - g->pl.cam[0]) > 0)
			s->inf.a = ANGLE(asinf((s->inf.y - g->pl.cam[1]) / s->inf.dist));
		else if ((s->inf.y - g->pl.cam[1]) > 0)
			s->inf.a = ANGLE(acosf((s->inf.x - g->pl.cam[0]) / s->inf.dist));
		else
			s->inf.a = ANGLE(-acosf((s->inf.x - g->pl.cam[0])
			/ s->inf.dist));
		s->inf.size = s->inf.tall * g->cnst / s->inf.dist;
		s->inf.a_limit = ((s->inf.size * 0.5) / g->screen->w) * SPECTRE;
		s->inf.a_min = ANGLE(s->inf.a - s->inf.a_limit);
		s->inf.a_max = ANGLE(s->inf.a + s->inf.a_limit);
		s = s->next;
	}
}

void	sort_sprites(t_gen *gen)
{
	t_sprite		**current;
	t_sprite_infos	tmp;

	current = &gen->sprites;
	while (*current && (*current)->next)
	{
		if ((*current)->next->inf.dist > (*current)->inf.dist)
		{
			tmp = (*current)->inf;
			(*current)->inf = (*current)->next->inf;
			(*current)->next->inf = tmp;
			current = &gen->sprites;
		}
		else
			current = &(*current)->next;
	}
}

void	walked_sprite_action(t_gen *gen)
{
	if (gen->walked_sprite && (gen->walked_sprite->inf.rep == 2
			|| gen->walked_sprite->inf.rep == 3
			|| gen->walked_sprite->inf.rep == 5))
	{
		if (gen->walked_sprite->inf.rep == 2)
			++gen->pl.coins;
		if (gen->walked_sprite->inf.rep == 3)
			gen->pl.munitions += 5;
		if (gen->walked_sprite->inf.rep == 5)
			gen->pl.keys |= 0x1;
		gen->walked_sprite->inf.rep |= S_HIDE;
	}
	gen->walked_sprite = NULL;
}
