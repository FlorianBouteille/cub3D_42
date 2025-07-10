/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:23:19 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/10 17:15:14 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_data(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}

void	free_wall(t_wallinfo *wall)
{
	t_wallinfo	*tmp;

	while (wall)
	{
		tmp = wall;
		wall = wall->next;
		free(tmp);
	}
}
void 	free_texture(t_mapinfo *info, t_texture *texture)
{
	if (texture->path)
		free(texture->path);
	if (texture->img)
		mlx_destroy_image(info->data->mlx, texture->img);
	if (texture->pixels)
		free(texture->pixels);
	free(texture);
	
}
void	free_mapinfo(t_mapinfo *info)
{
	if (info->north)
		free_texture(info, info->north);
	if (info->south)
		free_texture(info, info->south);
	if (info->east)
		free_texture(info, info->east);
	if (info->west)
		free_texture(info, info->west);
	if (info->minimap.img)
		mlx_destroy_image(info->data->mlx, info->minimap.img);
	if (info->frame.img)
		mlx_destroy_image(info->data->mlx, info->frame.img);
	if (info->data)
		free_data(info->data);
	if (info->wall)
		free_wall(info->wall);
	free(info->floor_color);
	free(info->ceiling_color);
	if (info->map)
		ft_free_tab(info->map);
	free(info->ray_info);
	free(info);
}

void	exit_clean(char *message, t_mapinfo *info, char **parsed)
{
	printf("%s\n", message);
	if (info)
		free_mapinfo(info);
	if (parsed)
		ft_free_tab(parsed);
	exit(1);
}
int	exit_clean_null(t_mapinfo *info)
{
	exit_clean("See you later", info, NULL);
	return (-9878);
}