/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:34:22 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/09 18:14:27 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	minimap_pixel_put(t_img_buffer *img_buffer, int x, int y, int color)
{
	char	*dst;

	dst = img_buffer->addr + (y * img_buffer->line_length + x
			* (img_buffer->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_mapinfo *info, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->map_scale)
	{
		j = 0;
		while (j < info->map_scale)
		{
			minimap_pixel_put(&info->minimap, y + j, x + i, color);
			j++;
		}
		i++;
	}
}

void	display_map(t_mapinfo *info, int display)
{
	draw_vectors(info, info->width, PI / 3);
	if (display)
		mlx_put_image_to_window(info->data->mlx, info->data->win,
			info->minimap.img, 0, 0);
}

void	draw_minimap(t_mapinfo *info, int display)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == '1')
				color = 0xDE5678;
			else if (ft_strchr("NSEW0", info->map[i][j]))
				color = 0x333333;
			else
				color = 0x000000;
			draw_square(info, info->map_scale * i, info->map_scale * j, color);
			draw_square(info, info->player_y_mini - info->map_scale / 2,
				info->player_x_mini - info->map_scale / 2, 0xFF0000);
			j++;
		}
		i++;
	}
	display_map(info, display);
}
