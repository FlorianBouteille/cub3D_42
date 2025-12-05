/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:43 by mhanarte          #+#    #+#             */
/*   Updated: 2025/08/25 12:11:51 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_door_textures(t_mapinfo *info)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		free_texture(info, info->door_textures[i]);
		i++;
	}
	free(info->door_textures);
}

void	free_lizard_textures(t_mapinfo *info)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		if (!info)
			return ;
		if (info->lizard_textures[i])
			free_texture(info, info->lizard_textures[i]);
		i++;
	}
	free(info->lizard_textures);
}

void	free_door(t_door *door)
{
	t_door	*tmp;

	while (door)
	{
		tmp = door;
		door = door->next;
		free(tmp);
	}
}

void	ft_free_int_tab(int **tab)
{
	int	i;

	i = 0;
	while (tab[i][0] != -1 && tab[i][1] != -1)
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}

void	free_extra_textures(t_mapinfo *info)
{
	if (info->door_textures)
		free_door_textures(info);
	if (info->lizard_textures)
		free_lizard_textures(info);
}
