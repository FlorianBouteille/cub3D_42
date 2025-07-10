/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:49:39 by mhanarte          #+#    #+#             */
/*   Updated: 2025/07/10 17:34:33 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_pixel(t_mapinfo *info, int y, int x, int len)
{
	int	x1;
	int	y1;
	int	draw_start;
	t_texture *texture;
	
	if (info->ray_info[x].direction == NO)
		texture = info->north;
	else if (info->ray_info[x].direction == SO)
		texture = info->south;
	else if (info->ray_info[x].direction == EA)
		texture = info->east;
	else
		texture = info->west;
	draw_start = (info->height - len) / 2;
	x1 = info->ray_info[x].wall_x * texture->width;
	if (len == 0)
		len = 1;
	y1 = ((y - draw_start) * texture->height) / len;
	if (y1 >= texture->height)
		y1 = texture->height - 1;
	return (texture->pixels[y1 * texture->width + x1]);
}
