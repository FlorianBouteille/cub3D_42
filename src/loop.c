/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:20:40 by mhanarte          #+#    #+#             */
/*   Updated: 2025/07/07 12:37:17 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	loop(t_mapinfo *info)
{
	mlx_loop_hook(info->data->mlx, update, info);
	mlx_loop(info->data->mlx);
}
