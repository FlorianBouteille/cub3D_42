/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:49:42 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/10 14:04:55 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_vertical(t_mapinfo *info, int index)
{
	int	i;
	int	len;
	int	diff;
	int diff_len;
	int	color;

	len = info->height / info->ray_info[index].vector_len;
	i = 0;
	diff = (info->height - len) / 2;
	diff_len = diff + len;
	while (i < info->height)
	{
		if (i < diff)
		color = info->ceiling_color_int;
		else if (i > diff_len)
		color = info->floor_color_int;
		else
		color = get_pixel(info, i, index, len);
		my_pixel_put(&info->frame, index, i, color);
		i++;
	}
}

void	draw_frame(t_mapinfo *info)
{
	int i;

	i = 0;
	while (i < info->width)
	{
		draw_vertical(info, i);
		i++;
	}
	mlx_put_image_to_window(info->data->mlx, info->data->win, info->frame.img,
		0, 0);
}
