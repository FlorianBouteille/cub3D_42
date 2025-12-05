/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:18:39 by mhanarte          #+#    #+#             */
/*   Updated: 2025/08/25 14:55:32 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*safe_xpm_to_img(void *mlx, char *path, t_mapinfo *info,
		t_texture *texture)
{
	int		w;
	int		h;
	void	*img;

	if (!path)
		exit_clean("Error\ntexture path is NULL\n", info, NULL);
	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
	{
		ft_putstr_fd("Error\nimpossible to load : ", 2);
		ft_putstr_fd(path, 2);
		free(path);
		exit_clean("\n", info, NULL);
	}
	texture->width = w;
	texture->height = h;
	free(path);
	return (img);
}

t_texture	*load_texture(t_mapinfo *info, t_texture *texture, char *path)
{
	int	bpp;
	int	endian;
	int	size_line;

	texture = malloc(sizeof(t_texture));
	texture->path = NULL;
	texture->img = safe_xpm_to_img(info->data->mlx, ft_strdup(path), info,
			texture);
	texture->pixels = (int *)mlx_get_data_addr(texture->img, &bpp, &size_line,
			&endian);
	texture->size_line = size_line / 4;
	return (texture);
}

void	load_img(t_mapinfo *info)
{
	int	bpp;
	int	endian;
	int	size_line;

	load_extra_textures(info);
	free(info->north->path);
	free(info->north);
	info->north = info->lizard_textures[0];
	info->south->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->south->path, " \n"), info, info->south);
	info->south->pixels = (int *)mlx_get_data_addr(info->south->img, &bpp,
			&size_line, &endian);
	info->south->size_line = size_line / 4;
	info->east->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->east->path, " \n"), info, info->east);
	info->east->pixels = (int *)mlx_get_data_addr(info->east->img, &bpp,
			&size_line, &endian);
	info->east->size_line = size_line / 4;
	info->west->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->west->path, " \n"), info, info->west);
	info->west->pixels = (int *)mlx_get_data_addr(info->west->img, &bpp,
			&size_line, &endian);
	info->west->size_line = size_line / 4;
}
