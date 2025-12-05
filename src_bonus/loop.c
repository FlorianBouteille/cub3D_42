/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:20:40 by mhanarte          #+#    #+#             */
/*   Updated: 2025/07/21 13:11:14 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	loop(t_mapinfo *info)
{
	mlx_loop_hook(info->data->mlx, update, info);
	mlx_loop(info->data->mlx);
}
