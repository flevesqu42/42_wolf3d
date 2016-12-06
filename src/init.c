/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 07:48:45 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:29:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	error_bis(int err)
{
	if (err == TTF_ERROR)
	{
		ft_putstr_fd("TTF failed : ", 2);
		ft_putstr_fd(TTF_GetError(), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (err == MAP_CORRUPT)
		ft_putstr_fd("Map generator failed : Linked map is corrupted.\n", 2);
}

void		error(int err)
{
	if (err == GUI_ERROR)
	{
		ft_putstr_fd("GUI failed : ", 2);
		ft_putstr_fd(SDL_GetError(), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (err == MAP_ERROR)
	{
		ft_putstr_fd("Map generator failed : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (err == MEM_ERROR)
	{
		ft_putstr_fd("Memory allocation failed : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
		error_bis(err);
	exit(1);
}

void		init_game(t_gen *gen)
{
	gen->run = 4.0;
	gen->commentary = NULL;
	gen->map = NULL;
	gen->fps = 15;
	gen->clock = 0;
	gen->rep = 0 | GAME_MODE;
	gen->fps = 31;
	gen->rep |= GUI_CONTINUE;
	gen->y_pos = Y / 2;
	gen->pl.coins = 0;
	gen->blocks_counter = 0;
	gen->pl.life = MAX_LIFE;
	gen->pl.munitions = 10;
	gen->sprites = NULL;
	gen->pointed_sprite = NULL;
	gen->walked_sprite = NULL;
	gen->wall_type = 1;
}

void		init_gen(t_gen *gen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || !(gen->win = SDL_CreateWindow("wolf3d"
			, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, X, Y
			, SDL_WINDOW_RESIZABLE)))
		error(GUI_ERROR);
	if (!(gen->screen = SDL_GetWindowSurface(gen->win)))
		error(GUI_ERROR);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_SetWindowIcon(gen->win, gen->medias.coin);
	load_medias(gen);
}

void		init_threads(t_gen *gen)
{
	int	index;

	index = 0;
	while (index < MT)
	{
		gen->mt[index].gen = gen;
		gen->mt[index].rep = 0;
		gen->mt[index].x_min = index * (gen->screen->w / MT);
		gen->mt[index].x_max = gen->mt[index].x_min + (gen->screen->w / MT);
		gen->mt[index].a = index * (gen->screen->w / MT) * A_DIST;
		++index;
	}
	gen->mt[MT - 1].x_max = gen->screen->w;
	gen->cnst = DIST_CAM;
}
