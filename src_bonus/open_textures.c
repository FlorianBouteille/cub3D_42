/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:35:11 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 12:11:42 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_lizard_textures(t_mapinfo *info)
{
	info->lizard_textures = malloc(sizeof(t_texture) * 11);
	if (!info->lizard_textures)
		return ;
	info->lizard_textures[0] = load_texture(info, info->lizard_textures[0],
			"textures/cobble_wall_0.xpm");
	info->lizard_textures[1] = load_texture(info, info->lizard_textures[1],
			"textures/cobble_wall_2.xpm");
	info->lizard_textures[2] = load_texture(info, info->lizard_textures[2],
			"textures/cobble_wall_3.xpm");
	info->lizard_textures[3] = load_texture(info, info->lizard_textures[3],
			"textures/cobble_wall_4.xpm");
	info->lizard_textures[4] = load_texture(info, info->lizard_textures[4],
			"textures/cobble_wall_5.xpm");
	info->lizard_textures[5] = load_texture(info, info->lizard_textures[5],
			"textures/cobble_wall_6.xpm");
	info->lizard_textures[6] = load_texture(info, info->lizard_textures[6],
			"textures/cobble_wall_7.xpm");
	info->lizard_textures[7] = load_texture(info, info->lizard_textures[7],
			"textures/cobble_wall_8.xpm");
	info->lizard_textures[8] = load_texture(info, info->lizard_textures[8],
			"textures/cobble_wall_9.xpm");
	info->lizard_textures[9] = load_texture(info, info->lizard_textures[9],
			"textures/cobble_wall_10.xpm");
	info->lizard_textures[10] = load_texture(info, info->lizard_textures[9],
			"textures/cobble_wall_11.xpm");
}

void	load_door_textures(t_mapinfo *info)
{
	info->door_textures = malloc(sizeof(t_texture) * 7);
	if (!info->door_textures)
		return ;
	info->door_textures[0] = load_texture(info, info->door_textures[0],
			"./textures/door_closed.xpm");
	info->door_textures[1] = load_texture(info, info->door_textures[1],
			"./textures/door_1.xpm");
	info->door_textures[2] = load_texture(info, info->door_textures[2],
			"./textures/door_2.xpm");
	info->door_textures[3] = load_texture(info, info->door_textures[3],
			"./textures/door_3.xpm");
	info->door_textures[4] = load_texture(info, info->door_textures[4],
			"./textures/door_4.xpm");
	info->door_textures[5] = load_texture(info, info->door_textures[5],
			"./textures/door_5.xpm");
	info->door_textures[6] = load_texture(info, info->door_textures[6],
			"./textures/door_open.xpm");
	return ;
}

void	load_extra_textures(t_mapinfo *info)
{
	load_door_textures(info);
	load_lizard_textures(info);
}
