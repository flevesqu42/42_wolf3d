/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 15:41:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/07 09:43:49 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_square(t_gen *gen, int *xy_min, int *xy_max, int color)
{
	int	xy[2];

	xy[1] = xy_min[1];
	while (++xy[1] < xy_max[1] && (xy[0] = xy_min[0]))
		while (++xy[0] < xy_max[0])
		{
			put_pixel_alpha(gen->screen, xy[0], xy[1]
				, (xy[1] > xy_max[1] - 2
				|| xy[1] < xy_min[1] + 2
				|| xy[0] < xy_min[0] + 2
				|| xy[0] > xy_max[0] - 2
				? 0xa0000000 : color));
		}
}

void	menu_action(t_gen *g, int i)
{
	if (g->rep & MOUSE_2)
	{
		if (i == 0)
			g->rep ^= MENU;
		else if (i == 1 || i == 2)
		{
			new_game(g, g->file, i == 2 ? "maps/backup1.wolf3d" : g->file);
			return ;
		}
		else if (i == 3)
			g->rep ^= GAME_MODE;
		else if (i == 4 && !(g->pl.coins = 0))
			free_sprites(&g->sprites);
		else if (i == 5)
		{
			g->rep ^= RELATIVE_MOUSE;
			SDL_SetRelativeMouseMode(g->rep & RELATIVE_MOUSE
				? SDL_FALSE : SDL_TRUE);
		}
		else if (i == 6)
			save_map(g);
		else if (i == 7)
			g->rep ^= GUI_CONTINUE;
		g->rep ^= MOUSE_2;
	}
}

void	display_menu(t_gen *gen)
{
	static char		str1[5] = "MENU";
	static char		menu[8][100] = {">_ Resume", ">_ Reload", ">_ New game"
		, ">_ Actual mode : ", ">_ Destroy all sprites"
		, ">_ Relative mouse mode: ", ">_ Save game", ">_ Exit"};
	static int		index = 0;
	static int		xy[2];

	index = -1;
	xy[0] = (gen->screen->w >> 1) - 30;
	xy[1] = (gen->screen->h >> 3) + 30;
	ft_strcpy(&menu[5][24], gen->rep & RELATIVE_MOUSE ? "[OFF]" : "[ON]");
	ft_strcpy(&menu[3][17], gen->rep & GAME_MODE ? "[GAME]" : "[EDITOR]");
	push_text(str1, gen, xy, COLOR_WHITE);
	while (++index < 8)
	{
		xy[0] = (gen->screen->w >> 2);
		xy[1] = (gen->screen->h >> 2) + (index * 60);
		if (gen->mouse[1] < xy[1] + 40 && gen->mouse[1] > xy[1])
		{
			push_text(menu[index], gen, xy, COLOR_WHITE);
			menu_action(gen, index);
		}
		else
			push_text(menu[index], gen, xy, COLOR_GREY);
	}
}

void	integrate_menu(t_gen *gen)
{
	put_square(gen
		, (int[2]){(gen->screen->w >> 3), (gen->screen->h >> 3)}
		, (int[2]){gen->screen->w - ((gen->screen->w >> 3))
		, gen->screen->h - ((gen->screen->h >> 3))}, 0x50a05000);
	display_menu(gen);
	print_cursor(gen->screen, gen->mouse[0], gen->mouse[1]);
}
