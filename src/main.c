/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 02:11:15 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:28:24 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_map(t_gen *gen)
{
	gen->y_max += 2;
	while (gen->y_max)
	{
		free(gen->map[(int)gen->y_max - 1]);
		gen->map[(int)gen->y_max - 1] = NULL;
		gen->y_max--;
	}
	free(gen->map);
	gen->map = NULL;
}

void	free_sprites(t_sprite **sprites)
{
	if (!(*sprites))
		return ;
	if ((*sprites)->next)
		free_sprites(&(*sprites)->next);
	free(*sprites);
	*sprites = NULL;
}

void	def_block_counter(t_gen *gen)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < gen->y_max && !(x = 0))
		while (++x < gen->x_max)
			if (!gen->map[y][x])
				++gen->blocks_counter;
}

void	new_game(t_gen *gen, char *file, char *src)
{
	gen->file = src;
	free_map(gen);
	free_sprites(&gen->sprites);
	init_game(gen);
	read_map(gen);
	def_block_counter(gen);
	gen->file = file;
}

int		main(int ac, char **av)
{
	t_gen gen;

	gen.file = ac > 1 ? av[1] : "maps/lvl1.wolf3d";
	gen.keys = 0;
	init_gen(&gen);
	init_game(&gen);
	read_map(&gen);
	def_block_counter(&gen);
	init_threads(&gen);
	game_loop(&gen);
	SDL_FreeSurface(gen.screen);
	SDL_FreeSurface(gen.medias.floor);
	SDL_FreeSurface(gen.medias.sky);
	SDL_FreeSurface(gen.medias.wall);
	SDL_FreeSurface(gen.medias.ceil);
	TTF_CloseFont(gen.medias.font[0]);
	TTF_CloseFont(gen.medias.font[1]);
	SDL_DestroyWindow(gen.win);
	TTF_Quit();
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_Quit();
	free_map(&gen);
	free_sprites(&gen.sprites);
	return (0);
}
