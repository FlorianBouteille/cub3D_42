/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:31:10 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/10 16:57:04 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	alloc_textures(t_mapinfo *info)
{
	info->north = malloc(sizeof(t_texture));
	if (!info->north)
		exit_clean("alloc fail\n", info, NULL);
	ft_memset(info->north, 0, sizeof(t_texture));
	info->south = malloc(sizeof(t_texture));
	if (!info->south)
		exit_clean("alloc fail\n", info, NULL);
	ft_memset(info->south, 0, sizeof(t_texture));
	info->east = malloc(sizeof(t_texture));
	if (!info->east)
		exit_clean("alloc fail\n", info, NULL);
	ft_memset(info->east, 0, sizeof(t_texture));
	info->west = malloc(sizeof(t_texture));
	if (!info->west)
		exit_clean("alloc fail\n", info, NULL);
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
	info->width = 40 * 64;
	info->height = 21 * 64;
	info->player_speed = 1;
	info->ray_info = malloc(info->width * sizeof(t_ray));
	if (!(info->ray_info))
		return (NULL);	
	ft_memset(info->ray_info, 0, sizeof(t_ray));
	alloc_textures(info);
	return (info);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 40 * 64, 21 * 64, "cub3D");
	return (data);
}

t_wallinfo	*init_wallinfo(int x, int y, t_wallinfo *head)
{
	t_wallinfo	*new;
	t_wallinfo	*ptr;

	ptr = head;
	new = malloc(sizeof(t_wallinfo));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (!ptr)
		return (new);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (head);
}
void	init_img_buffer(t_mapinfo *info, t_img_buffer *img_buffer, int width,
		int height)
{
	img_buffer->img = mlx_new_image(info->data->mlx, width, height);
	img_buffer->addr = mlx_get_data_addr(img_buffer->img,
			&img_buffer->bits_per_pixel, &img_buffer->line_length,
			&img_buffer->endian);
}
