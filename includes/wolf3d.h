/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 02:11:13 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:44:09 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <fcntl.h>
# include <OpenCL/opencl.h>

# define X 1900
# define Y 1200

# define MT	16

# define TAU			6.28318530718

# define MAX_LIFE 		100

# define TALL_NORMAL	0.5
# define TALL_ANT		0.1
# define TALL_GIANT		0.9

# define GUI_CONTINUE	0x1
# define MOUSE_1		0x2
# define MOUSE_2		0x4
# define RELATIVE_MOUSE	0x8
# define EDIT_SPRITE	0x10
# define SET_COIN		0x20
# define SET_SMITH		0x40
# define SET_MUN		0x80
# define SET_BOSS		0x100
# define SET_KEY		0x200
# define MENU			0x400
# define SAVE_MAP		0x800
# define GAME_MODE		0x1000
# define SHOOT			0x2000
# define VICTORY		0x4000

# define WALL_HORIZONTAL	0x1

# define GUI_ERROR		1
# define MEM_ERROR		2
# define MAP_ERROR		3
# define TTF_ERROR		4
# define MAP_CORRUPT	5

# define CLASSIC_ENEMY_LIFE	2
# define BOSS_ENEMY_LIFE	20

# define S_HIDE 0x80

# define ABS(i)				((i < 0.0 ? -i : i))
# define ANGLE(a)			(a < 0 ? TAU + a : fmod(a, TAU))
# define SPECTRE			(1.22)
# define A_LIMIT			(SPECTRE * 0.5)
# define A_LESS(al)			ANGLE(al - A_LIMIT)
# define A_DIST				(SPECTRE / (gen->screen->w + 1))
# define DIST_CAM			(((gen->screen->w >> 1)) / tanf(A_LIMIT))
# define VER(av, ad, dir)	(ABS((tanf(av)) * ad) * dir)
# define HOR(ah, op, dir)	(ABS(op / (tanf(ah))) * dir)
# define DIST_FINAL(dist)	(gen->cnst / dist)

# define MAGIC				"\0B*WOLF="

# define COLOR_GREY			(SDL_Color){0xa0, 0xa0, 0xa0, 0xff}
# define COLOR_WHITE		(SDL_Color){0xff, 0xff, 0xff, 0xff}
# define COLOR_ORANGE		(SDL_Color){0xff, 0xa0, 0x00, 0xff}
# define COLOR_YELLOW		(SDL_Color){0xff, 0xcc, 0x00, 0xff}
# define COLOR_BLACK		(SDL_Color){0x00, 0x00, 0x00, 0xff}

typedef struct	s_sprite_infos
{
	int				rep;
	unsigned int	filter;
	float			x;
	float			y;
	float			dist;
	float			size;
	float			a;
	float			a_min;
	float			a_max;
	float			height;
	float			tall;
	float			a_limit;
}				t_sprite_infos;

typedef struct	s_sprite
{
	struct s_sprite_infos	inf;
	struct s_sprite			*next;
}				t_sprite;

typedef struct	s_thread
{
	long			rep;
	int				x_min;
	int				x_max;
	float			a;
	float			x;
	float			coords_hor[2];
	float			coords_ver[2];
	float			*coords_final;
	unsigned char	*cell;
	float			coord_wall;
	float			dist[3];
	float			dir[2];
	size_t			decrease;
	pthread_t		thread;
	void			*gen;
}				t_thread;

typedef struct	s_medias
{
	SDL_Surface	*floor;
	SDL_Surface	*ceil;
	SDL_Surface	*sky;
	SDL_Surface	*gold;
	SDL_Surface	*wall;
	SDL_Surface	*coin;
	SDL_Surface	*smith;
	SDL_Surface	*boss;
	SDL_Surface *key;
	SDL_Surface	*mun;
	SDL_Surface	*shoot;
	TTF_Font	*font[3];
	SDL_Surface	*hex;
	SDL_Surface	*door[6];
	SDL_Surface	*hdoor[6];
}				t_medias;

typedef struct	s_player
{
	float		cam[3];
	size_t		coins;
	size_t		munitions;
	size_t		life;
	long		keys;
}				t_player;

typedef struct	s_gen
{
	long			rep;
	long			keys;
	t_player		pl;
	SDL_Surface		*screen;
	unsigned char	*pointed_block;
	float			pointed_coord[2];
	int				fps;
	char			wall_type;
	t_sprite		*sprites;
	t_sprite		*pointed_sprite;
	t_sprite		*walked_sprite;
	float			run;
	float			tall;
	int				y_pos;
	int				mouse[2];
	size_t			blocks_counter;
	clock_t			clock;
	unsigned char	**map;
	int				x_max;
	int				y_max;
	float			cnst;
	t_medias		medias;
	t_thread		mt[MT];
	SDL_Window		*win;
	char			*file;
	char			*commentary;
}				t_gen;

void			error(int err);

SDL_Surface		*get_surface(char infos, t_medias *medias);
SDL_Surface		*get_sprite(char infos, t_medias *medias);

void			keydown_event(SDL_Event *event, t_gen *gen);
void			keyup_event(SDL_Event *event, t_gen *gen);

void			free_sprites(t_sprite **sprites);

void			set_surface(SDL_Surface *screen, SDL_Surface *src, int xs
		, int ys);

void			set_sprites(t_gen *gen, t_thread *thr, float a);
void			new_sprite(t_sprite **sprites, int rep, t_gen *gen);
void			delete_sprite(t_gen *gen, t_sprite *sprite);

void			*graphical_events(void *t);
void			read_map(t_gen *gen);
int				get_color_surface(float x, float y, SDL_Surface *surface);
void			gui_events(t_gen *gen);
void			init_game(t_gen *gen);
void			init_gen(t_gen *gen);
void			load_medias(t_gen *gen);
void			init_threads(t_gen *gen);
void			game_loop(t_gen *gen);
int				get_shadow(int color, char hor);
int				get_color_surface(float x, float y, SDL_Surface *surface);
void			print_cursor(SDL_Surface *surface, int x, int y);
void			get_distance(float a, t_thread *thread, t_gen *gen
	, float *dist);
void			blit_surface(SDL_Surface *screen, int x, int y
		, SDL_Surface *text);
void			put_pixel(SDL_Surface *screen, size_t x, size_t y
	, unsigned int color);
void			put_pixel_alpha(SDL_Surface *screen, size_t x, size_t y
	, unsigned int color);

void			save_map(t_gen *gen);
void			integrate_menu(t_gen *gen);
void			push_text(char *str, t_gen *gen, int *xy, SDL_Color color);

int				lifemask(t_gen *gen, int color);

void			print_sprites(t_gen *g, t_sprite *c, int x, float a);

void			move_actions(t_gen *gen);
void			strafes_actions(t_gen *gen);
void			mouse_actions_game(t_gen *gen);
void			mouse_actions_editor(t_gen *gen);

void			text_actions(t_gen *gen);

void			open_door(t_gen *gen);

void			sort_sprites(t_gen *gen);
void			init_sprites(t_gen *gen);
void			edit_sprite_actions(t_gen *gen);
void			walked_sprite_action(t_gen *gen);

void			go_threads(t_gen *gen);

void			put_square(t_gen *gen, int *xy_min, int *xy_max, int color);

void			free_map(t_gen *gen);
void			new_game(t_gen *gen, char *file, char *src);
void			def_block_counter(t_gen *gen);

void			set_pointed_sprite(t_gen *gen);

#endif
