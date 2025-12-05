/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:53:58 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 15:25:07 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	animate_wall(t_mapinfo *info)
{
	static int	anim_on;
	static int	anim_frame;
	static int	game_tick;

	if (anim_on == 1)
	{
		if (game_tick % 7 == 0)
			info->north = info->lizard_textures[anim_frame++];
		if (anim_frame == 11)
		{
			anim_on = 0;
			anim_frame = 0;
		}
	}
	else
	{
		if (rand() % 100 == 0)
		{
			anim_on = 1;
			game_tick = 0;
		}
	}
	game_tick++;
}
