/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 06:18:11 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/14 14:42:45 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	read_map_walls(t_gen *gen, int fd)
{
	int index;

	index = 0;
	if (read(fd, &gen->x_max, sizeof(int)) < (long)sizeof(int)
			|| gen->x_max > 500)
		error(MAP_CORRUPT);
	if (read(fd, &gen->y_max, sizeof(int)) < (long)sizeof(int))
		error(MAP_CORRUPT);
	if (!(gen->map = (unsigned char**)ft_memalloc(sizeof(unsigned char*)
			* (gen->y_max + 2))))
		error(MEM_ERROR);
	while (index < gen->y_max + 2)
	{
		if (!(gen->map[index] = (unsigned char*)ft_memalloc(
			sizeof(unsigned char) * (gen->x_max + 2))))
			error(MEM_ERROR);
		if (index == 0 || index == gen->y_max - 1)
			ft_memset(gen->map[index], 0x80, gen->x_max + 2);
		else if (read(fd, &gen->map[index][1], gen->x_max * sizeof(char))
					< (long)(gen->x_max * sizeof(char)))
			error(MAP_CORRUPT);
		gen->map[index][0] = 0x80;
		gen->map[index][gen->x_max + 1] = 0x80;
		index++;
	}
}

void	read_map_sprites(t_gen *gen, int fd)
{
	t_sprite	*new;
	int			index;

	if (read(fd, &index, sizeof(int)) < (long)sizeof(int))
		error(MAP_CORRUPT);
	while (index)
	{
		if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
			error(MEM_ERROR);
		if (read(fd, &new->inf, sizeof(t_sprite_infos))
				< (long)sizeof(t_sprite_infos))
			error(MAP_CORRUPT);
		new->next = gen->sprites;
		gen->sprites = new;
		--index;
	}
}

void	read_map(t_gen *gen)
{
	int			fd;
	char		buf[8];

	if ((fd = open(gen->file, O_RDONLY)) < 0)
		error(MAP_ERROR);
	if (read(fd, buf, 8) < 8 || ft_memcmp(buf, MAGIC, 8))
		error(MAP_CORRUPT);
	read_map_walls(gen, fd);
	if (read(fd, &gen->pl.cam[0], sizeof(float)) < (long)sizeof(float)
			|| gen->pl.cam[0] > gen->x_max + 1 || gen->pl.cam[0] < 1)
		error(MAP_CORRUPT);
	if (read(fd, &gen->pl.cam[1], sizeof(float)) < (long)sizeof(float)
			|| gen->pl.cam[0] > gen->y_max + 1 || gen->pl.cam[1] < 1)
		error(MAP_CORRUPT);
	if (read(fd, &gen->pl.cam[2], sizeof(float)) < (long)sizeof(float))
		error(MAP_CORRUPT);
	read_map_sprites(gen, fd);
	if (read(fd, &buf, 8) > 0)
		error(MAP_CORRUPT);
	close(fd);
}

void	save_map_sprites(t_gen *gen, int fd)
{
	int			index;
	t_sprite	*current;

	index = 0;
	current = gen->sprites;
	while (current && ++index)
		current = current->next;
	write(fd, &index, sizeof(int));
	current = gen->sprites;
	while (current)
	{
		if (current->inf.rep & S_HIDE)
			current->inf.rep ^= S_HIDE;
		if ((current->inf.rep & 0xff) == 1)
			current->inf.rep = (CLASSIC_ENEMY_LIFE << 8) | 1;
		if ((current->inf.rep & 0xff) == 4)
			current->inf.rep = (BOSS_ENEMY_LIFE << 8) | 4;
		write(fd, &current->inf, sizeof(t_sprite_infos));
		current = current->next;
	}
}

void	save_map(t_gen *gen)
{
	int			fd;
	int			index;
	t_sprite	*current;

	index = 0;
	current = gen->sprites;
	if ((fd = open(gen->file, O_WRONLY | O_TRUNC)) < 0)
		error(MAP_ERROR);
	write(fd, MAGIC, 8);
	write(fd, &gen->x_max, sizeof(int));
	write(fd, &gen->y_max, sizeof(int));
	while (++index < gen->y_max + 1)
		write(fd, &gen->map[index][1], gen->x_max * sizeof(char));
	write(fd, &gen->pl.cam[0], sizeof(float));
	write(fd, &gen->pl.cam[1], sizeof(float));
	write(fd, &gen->pl.cam[2], sizeof(float));
	save_map_sprites(gen, fd);
	close(fd);
	gen->commentary = "Map successfully saved !";
}
