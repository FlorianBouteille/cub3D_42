/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:49:42 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/22 14:53:31 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_vert
{
	int		i;
	int		len;
	int		diff;
	int		diff_len;
	int		color;
	char	*dst;
}			t_vert;

void	draw_vertical(t_mapinfo *info, int index)
{
	t_vert	*vert;

	vert = malloc(sizeof(t_vert));
	vert->len = info->height / info->ray_info[index].vector_len;
	vert->i = 0;
	vert->diff = (info->height - vert->len) / 2;
	vert->diff_len = vert->diff + vert->len;
	vert->dst = info->frame.addr + index * (info->frame.bits_per_pixel / 8);
	while (vert->i < info->height)
	{
		if (vert->i < vert->diff)
			vert->color = info->ceiling_color_int;
		else if (vert->i > vert->diff_len)
			vert->color = info->floor_color_int;
		else
			vert->color = get_pixel(info, vert->i, index, vert->len);
		*(unsigned int *)(vert->dst + vert->i
				* info->frame.line_length) = vert->color;
		vert->i++;
	}
	free(vert);
}

void	draw_frame(t_mapinfo *info)
{
	int	i;

	i = 0;
	if (info->doors_opening)
		animate_door(info);
	animate_wall(info);
	while (i < info->width)
	{
		draw_vertical(info, i);
		i++;
	}
	mlx_put_image_to_window(info->data->mlx, info->data->win, info->frame.img,
		0, 0);
}
