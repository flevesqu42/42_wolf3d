/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 07:50:06 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:33:08 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pixel(SDL_Surface *screen, size_t x, size_t y, unsigned int color)
{
	if (y >= (size_t)screen->h || x >= (size_t)screen->w)
		return ;
	((int*)screen->pixels)[(y * screen->w) + x] = color;
}

void	put_pixel_alpha(SDL_Surface *screen, size_t x, size_t y
	, unsigned int color)
{
	int	alpha;
	int *pixels;

	if (y >= (size_t)screen->h || x >= (size_t)screen->w)
		return ;
	pixels = &((int*)screen->pixels)[(y * screen->w) + x];
	alpha = (color & 0xff000000) >> 24;
	*pixels = ((((color & 0x0000ff) * alpha) / 0xff)
		| (((((color & 0x00ff00) >> 8) * alpha) / 0xff) << 8)
		| (((((color & 0xff0000) >> 16) * alpha) / 0xff) << 16))
		+ ((((*pixels & 0x0000ff) * (0xff - alpha)) / 0xff)
		| (((((*pixels & 0x00ff00) >> 8) * (0xff - alpha)) / 0xff) << 8)
		| (((((*pixels & 0xff0000) >> 16) * (0xff - alpha)) / 0xff) << 16));
}

int		get_shadow(int color, char hor)
{
	if (hor)
		return (((color & 0x0000ff) >> 1)
			| ((((color & 0x00ff00) >> 8) >> 1) << 8)
			| ((((color & 0xff0000) >> 16) >> 1) << 16)
			| (color & 0xff000000));
	else
		return (color);
}

int		lifemask(t_gen *gen, int pixel)
{
	int	life;

	if (!(gen->rep & GAME_MODE))
		return (pixel);
	life = gen->pl.life * 0xff / MAX_LIFE;
	return ((((pixel & 0x0000ff) * life) / 0xff)
		| (((((pixel & 0x00ff00) >> 8) * life) / 0xff) << 8)
		| (pixel & 0xffff0000));
}

void	blit_surface(SDL_Surface *screen, int x, int y, SDL_Surface *text)
{
	static int	index_x;
	static int	index_y;

	index_y = 0;
	while (index_y < text->h)
	{
		index_x = 0;
		while (index_x < text->w)
		{
			put_pixel_alpha(screen, x + index_x, y + index_y
				, ((int*)text->pixels)[(index_y * text->w) + (index_x)]);
			++index_x;
		}
		++index_y;
	}
}
