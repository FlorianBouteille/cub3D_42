/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:31:10 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/19 15:05:2 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	alloc_textures(t_mapinfo *info)
{
	info->north = malloc(sizeof(t_texture));
	if (!info->north)
		exit_clean("Error\nalloc fail\n", info, NULL);
	ft_memset(info->north, 0, sizeof(t_texture));
	info->south = malloc(sizeof(t_texture));
	if (!info->south)
		exit_clean("Error\nalloc fail\n", info, NULL);
	ft_memset(info->south, 0, sizeof(t_texture));
	info->east = malloc(sizeof(t_texture));
	if (!info->east)
		exit_clean("Error\nalloc fail\n", info, NULL);
	ft_memset(info->east, 0, sizeof(t_texture));
	info->west = malloc(sizeof(t_texture));
	if (!info->west)
		exit_clean("Error\nalloc fail\n", info, NULL);
	ft_memset(info->west, 0, sizeof(t_texture));
}

t_mapinfo	*init_mapinfo(void)
{
	t_mapinfo	*info;

	info = malloc(sizeof(t_mapinfo));
	if (!info)
		return (NULL);
	ft_memset(info, '\0', sizeof(t_mapinfo));
	info->map_scale = 10;
	info->ms = info->map_scale / 2;
	info->player_speed = 1;
	alloc_textures(info);
	return (info);
}

t_data	*init_data(t_mapinfo *info)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &info->width, &info->height);
	info->ray_info = malloc(info->width * sizeof(t_ray));
	if (!(info->ray_info))
		return (NULL);
	ft_memset(info->ray_info, 0, sizeof(t_ray));
	data->win = mlx_new_window(data->mlx, info->width, info->height, "cub3D");
	return (data);
}

void	init_img_buffer(t_mapinfo *info, t_img_buffer *img_buffer, int width,
		int height)
{
	img_buffer->img = mlx_new_image(info->data->mlx, width, height);
	img_buffer->addr = mlx_get_data_addr(img_buffer->img,
			&img_buffer->bits_per_pixel, &img_buffer->line_length,
			&img_buffer->endian);
	mlx_mouse_move(info->data->mlx, info->data->win, info->width / 2,
		info->height / 2);
}
