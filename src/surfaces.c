/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surfaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 07:55:05 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:36:09 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				get_color_surface(float x, float y, SDL_Surface *surface)
{
	x *= surface->w;
	y *= (surface->h - 1);
	return (((int*)surface->pixels)[((int)y * surface->w + (int)x)]);
}

SDL_Surface		*get_sprite(char infos, t_medias *medias)
{
	if (infos == 1)
		return (medias->smith);
	else if (infos == 2)
		return (medias->coin);
	else if (infos == 3)
		return (medias->mun);
	else if (infos == 4)
		return (medias->boss);
	else
		return (medias->key);
}

/*
** In map, 0x80 bit is board, 0x70 bits are for gif, the others are for texture.
*/

SDL_Surface		*get_surface(char infos, t_medias *medias)
{
	if ((infos & 0x0f) == 0x02)
		return (medias->door[(infos & 0x70) >> 4]);
	if ((infos & 0x0f) == 0x04)
		return (medias->hdoor[(infos & 0x70) >> 4]);
	infos = infos & 0x0f;
	if (infos == 0x01)
		return (medias->wall);
	else if (infos == 0x03)
		return (medias->ceil);
	else if (infos == 0x05)
		return (medias->floor);
	else if (infos == 0x06)
		return (medias->gold);
	else
		return (medias->ceil);
}

void			print_cursor(SDL_Surface *surface, int x, int y)
{
	put_pixel(surface, x + 1, y, 0x00ffa000);
	put_pixel(surface, x - 1, y, 0x00ffa000);
	put_pixel(surface, x, y + 1, 0x00ffa000);
	put_pixel(surface, x, y - 1, 0x00ffa000);
	put_pixel(surface, x + 2, y, 0x00ffa000);
	put_pixel(surface, x - 2, y, 0x00ffa000);
	put_pixel(surface, x, y + 2, 0x00ffa000);
	put_pixel(surface, x, y - 2, 0x00ffa000);
	put_pixel(surface, x + 3, y, 0x00ffa000);
	put_pixel(surface, x - 3, y, 0x00ffa000);
	put_pixel(surface, x, y + 3, 0x00ffa000);
	put_pixel(surface, x, y - 3, 0x00ffa000);
}

void			set_surface(SDL_Surface *screen, SDL_Surface *src, int xs
		, int ys)
{
	int	xy[2];

	xy[1] = 0;
	while (++xy[1] < src->h)
	{
		xy[0] = 0;
		while (++xy[0] < src->w)
			put_pixel_alpha(screen, xy[0] + xs, xy[1] + ys
				, ((int*)src->pixels)[(xy[1] * src->w) + xy[0]]);
	}
}
