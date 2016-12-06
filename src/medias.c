/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medias.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:22:45 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/15 13:32:56 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	load_gif(t_gen *gen)
{
	if (!(gen->medias.door[0] = IMG_Load("./ressources/door.png"))
			|| !(gen->medias.door[1] = IMG_Load("./ressources/hex4.png"))
			|| !(gen->medias.door[2] = IMG_Load("./ressources/hex5.png"))
			|| !(gen->medias.door[3] = IMG_Load("./ressources/hex6.png"))
			|| !(gen->medias.door[4] = IMG_Load("./ressources/hex7.png"))
			|| !(gen->medias.door[5] = IMG_Load("./ressources/hex8.png"))
			|| !(gen->medias.hdoor[0] = IMG_Load("./ressources/hdoor0.png"))
			|| !(gen->medias.hdoor[1] = IMG_Load("./ressources/hdoor1.png"))
			|| !(gen->medias.hdoor[2] = IMG_Load("./ressources/hdoor2.png"))
			|| !(gen->medias.hdoor[3] = IMG_Load("./ressources/hdoor3.png"))
			|| !(gen->medias.hdoor[4] = IMG_Load("./ressources/hdoor4.png"))
			|| !(gen->medias.hdoor[5] = IMG_Load("./ressources/hdoor5.png")))
		error(GUI_ERROR);
}

void		load_medias(t_gen *gen)
{
	if (!(gen->medias.wall = IMG_Load("./ressources/wb.jpg"))
			|| !(gen->medias.sky = IMG_Load("./ressources/sky2.png"))
			|| !(gen->medias.floor = IMG_Load("./ressources/front.jpg"))
			|| !(gen->medias.gold = IMG_Load("./ressources/hex-gold.png"))
			|| !(gen->medias.ceil = IMG_Load("./ressources/hex3.png"))
			|| !(gen->medias.coin = IMG_Load("./ressources/gold.png"))
			|| !(gen->medias.key = IMG_Load("./ressources/key.png"))
			|| !(gen->medias.mun = IMG_Load("./ressources/norma.png"))
			|| !(gen->medias.shoot = IMG_Load("./ressources/shoot.png"))
			|| !(gen->medias.smith = IMG_Load("./ressources/vendor.png"))
			|| !(gen->medias.boss = IMG_Load("./ressources/boss.png"))
			|| (TTF_Init() < 0)
			|| !(gen->medias.font[0] = TTF_OpenFont("./ressources/Terminus.ttf"
				, 20))
			|| !(gen->medias.font[1] = TTF_OpenFont("./ressources/Raven.ttf"
				, 200))
			|| !(gen->medias.font[2] = TTF_OpenFont("./ressources/Terminus.ttf"
				, 200)))
		error(TTF_ERROR);
	load_gif(gen);
}
