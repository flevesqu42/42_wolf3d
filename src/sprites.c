/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 10:53:44 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:36:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		is_in_spectre(float min, float max, float a)
{
	if (min < max)
		return (a > min && a < max ? 1 : 0);
	else
		return (a > min || a < max ? 1 : 0);
}

void	set_sprites(t_gen *gen, t_thread *thr, float a)
{
	t_sprite	*current;

	current = gen->sprites;
	while (current)
	{
		if (!(current->inf.rep & S_HIDE)
				&& is_in_spectre(current->inf.a_min, current->inf.a_max, a)
				&& current->inf.dist < thr->dist[2])
		{
			if (current->inf.dist <= 1.0 && gen->rep & GAME_MODE)
				gen->walked_sprite = current;
			if (gen->pl.life > 0 && ((current->inf.rep & 0xff) == 1
						|| (current->inf.rep & 0xff) == 4)
					&& (gen->rep & (GAME_MODE | MENU)) == GAME_MODE)
				++thr->decrease;
			print_sprites(gen, current, thr->x, ANGLE(a - current->inf.a_min)
				/ (current->inf.a_limit * 2));
		}
		current = current->next;
	}
}

void	delete_sprite(t_gen *gen, t_sprite *sprite)
{
	static t_sprite	**current = NULL;

	current = &gen->sprites;
	while (*current)
	{
		if (*current == sprite)
		{
			free(*current);
			gen->pointed_sprite = NULL;
			*current = (*current)->next;
			if (gen->rep & MOUSE_1)
				gen->rep ^= MOUSE_1;
			return ;
		}
		current = &(*current)->next;
	}
}

void	set_sprite_caracs(int rep, t_sprite *new)
{
	if (rep == 2)
	{
		new->inf.tall = 0.15;
		new->inf.height = 0.10;
	}
	else if (rep == 3)
		new->inf.tall = 0.15;
	else if (rep == 1)
	{
		new->inf.tall = 0.55;
		new->inf.rep |= (CLASSIC_ENEMY_LIFE << 8);
	}
	else if (rep == 4)
	{
		new->inf.tall = 1.0;
		new->inf.rep |= (BOSS_ENEMY_LIFE << 8);
	}
	else if (rep == 5)
		new->inf.tall = 0.30;
}

void	new_sprite(t_sprite **sprites, int rep, t_gen *gen)
{
	t_sprite *new;

	if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
		error(MEM_ERROR);
	new->inf.rep = rep;
	new->inf.x = gen->pointed_coord[0];
	new->inf.y = gen->pointed_coord[1];
	new->inf.height = 0.0;
	set_sprite_caracs(rep, new);
	new->inf.filter = 0xffffffff;
	new->next = *sprites;
	*sprites = new;
}
