/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:14:11 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 15:03:25 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	strafes_actions(t_gen *g)
{
	static int	diff = 0;

	if (g->keys & 0x1)
	{
		if ((diff = (int)(g->pl.cam[0] + (cosf(ANGLE(g->pl.cam[2] + M_PI_2))
				/ g->run))) >= 0 && diff <= g->x_max
				&& !(0x8f & g->map[(int)(g->pl.cam[1])][diff]))
			g->pl.cam[0] += cosf(ANGLE(g->pl.cam[2] + M_PI_2)) / g->run;
		if ((diff = (int)(g->pl.cam[1] + (sinf(ANGLE(g->pl.cam[2] + M_PI_2))
				/ g->run))) >= 0 && diff <= g->y_max
				&& !(0x8f & g->map[diff][(int)(g->pl.cam[0])]))
			g->pl.cam[1] += sinf(ANGLE(g->pl.cam[2] + M_PI_2)) / g->run;
	}
	if (g->keys & 0x2)
	{
		if ((diff = (int)(g->pl.cam[0] + (cosf(ANGLE(g->pl.cam[2] - M_PI_2))
				/ g->run))) >= 0 && diff <= g->x_max
				&& !(0x8f & g->map[(int)(g->pl.cam[1])][diff]))
			g->pl.cam[0] += cosf(ANGLE(g->pl.cam[2] - M_PI_2)) / g->run;
		if ((diff = (int)(g->pl.cam[1] + (sinf(ANGLE(g->pl.cam[2] - M_PI_2))
				/ g->run))) >= 0 && diff <= g->y_max
				&& !(0x8f & g->map[diff][(int)(g->pl.cam[0])]))
			g->pl.cam[1] += sinf(ANGLE(g->pl.cam[2] - M_PI_2)) / g->run;
	}
}

void	move_actions(t_gen *g)
{
	static int	diff = 0;

	if (g->keys & 0x4)
	{
		if ((diff = (int)(g->pl.cam[0] + (cosf(g->pl.cam[2]) / g->run))) >= 0
				&& diff <= g->x_max && !(0x8f & g->map[(int)(g->pl.cam[1])]
				[diff]))
			g->pl.cam[0] += cosf(g->pl.cam[2]) / g->run;
		if ((diff = (int)(g->pl.cam[1] + (sinf(g->pl.cam[2]) / g->run))) >= 0
				&& diff <= g->y_max && !(0x8f & g->map[diff]
				[(int)(g->pl.cam[0])]))
			g->pl.cam[1] += sinf(g->pl.cam[2]) / g->run;
	}
	if (g->keys & 0x8)
	{
		if ((diff = (int)(g->pl.cam[0] - (cosf(g->pl.cam[2]) / g->run))) >= 0
				&& diff <= g->x_max && !(0x8f & g->map[(int)(g->pl.cam[1])]
				[diff]))
			g->pl.cam[0] -= cosf(g->pl.cam[2]) / g->run;
		if ((diff = (int)(g->pl.cam[1] - (sinf(g->pl.cam[2]) / g->run))) >= 0
				&& diff <= g->y_max && !(0x8f & g->map[diff]
				[(int)(g->pl.cam[0])]))
			g->pl.cam[1] -= sinf(g->pl.cam[2]) / g->run;
	}
}
