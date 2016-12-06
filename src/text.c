/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:19:23 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 15:21:47 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		push_text(char *str, t_gen *gen, int *xy, SDL_Color color)
{
	static SDL_Surface	*text = NULL;

	if (!(text = TTF_RenderText_Blended(gen->medias.font[0], str, color)))
		error(TTF_ERROR);
	blit_surface(gen->screen, xy[0], xy[1], text);
	SDL_FreeSurface(text);
}

static void	push_announce(t_gen *gen)
{
	static SDL_Surface	*text = NULL;

	if (gen->pl.life == 0)
	{
		if (!(text = TTF_RenderText_Blended(gen->medias.font[1], "Mind lost"
				, COLOR_BLACK)))
			error(TTF_ERROR);
		blit_surface(gen->screen, (gen->screen->w >> 1) - 500
			, (gen->screen->h >> 1) - 200, text);
		SDL_FreeSurface(text);
		gen->commentary = "Press <space bar> to reload game.";
	}
	if (gen->rep & VICTORY)
	{
		if (!(text = TTF_RenderText_Blended(gen->medias.font[2], "MIND KEPT !"
				, COLOR_YELLOW)))
			error(TTF_ERROR);
		blit_surface(gen->screen, (gen->screen->w >> 1) - 600
			, (gen->screen->h >> 1) - 200, text);
		SDL_FreeSurface(text);
		gen->commentary = "Press <space bar> to reload game.";
	}
}

static void	display_fps(t_gen *gen)
{
	static char			str2[10] = "Fps : ";
	static clock_t		last_clock = 0;
	static unsigned int	fps = 0;
	static int			xy[2];

	fps += 1;
	xy[0] = (gen->screen->w >> 4);
	xy[1] = (gen->screen->h >> 5);
	gen->clock = SDL_GetTicks();
	if (gen->clock - last_clock >= 1000)
	{
		last_clock = gen->clock;
		gen->fps = fps;
		fps = 0;
	}
	ft_utoasub(gen->fps, &str2[6]);
	push_text(str2, gen, xy, COLOR_ORANGE);
}

static void	display_blocks_or_coins(t_gen *gen)
{
	static char			str[2][26] = {"Remaining blocks : "
		, "Coins found : "};
	static int			xy[2];

	xy[1] = (gen->screen->h >> 5);
	if (gen->rep & GAME_MODE)
	{
		xy[0] = gen->screen->w - (gen->screen->w >> 3);
		ft_utoasub(gen->pl.coins, &str[1][14]);
		push_text(str[1], gen, xy, COLOR_ORANGE);
	}
	else
	{
		xy[0] = gen->screen->w - (gen->screen->w >> 3);
		ft_utoasub(gen->blocks_counter, &str[0][19]);
		push_text(str[0], gen, xy, COLOR_ORANGE);
	}
}

void		text_actions(t_gen *gen)
{
	static char			str[2][26] = {"Munitions : ", "Mental health : "};
	static int			xy[2];

	xy[0] = (gen->screen->w >> 1) - 100;
	xy[1] = (gen->screen->h >> 5);
	ft_utoasub(gen->pl.munitions, &str[0][12]);
	push_text(str[0], gen, xy, COLOR_ORANGE);
	xy[0] = (gen->screen->w >> 1) - 100;
	xy[1] = gen->screen ->h - ((gen->screen->h >> 5));
	ft_utoasub(gen->pl.life, &str[1][16]);
	push_text(str[1], gen, xy, COLOR_ORANGE);
	display_fps(gen);
	push_announce(gen);
	display_blocks_or_coins(gen);
}
