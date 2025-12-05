/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:34 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/21 11:56:44 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keyup(int keycode, t_mapinfo *info)
{
	if (keycode == 119)
		info->key_w = 0;
	if (keycode == 115)
		info->key_s = 0;
	if (keycode == 97)
		info->key_a = 0;
	if (keycode == 100)
		info->key_d = 0;
	if (keycode == 65361)
		info->look_left = 0;
	if (keycode == 65363)
		info->look_right = 0;
	if (keycode == 65505)
		info->player_speed = 1;
	return (0);
}

int	handle_keydown(int keycode, t_mapinfo *info)
{
	if (keycode == 119)
		info->key_w = 1;
	if (keycode == 115)
		info->key_s = 1;
	if (keycode == 97)
		info->key_a = 1;
	if (keycode == 100)
		info->key_d = 1;
	if (keycode == 101)
		open_door(info);
	if (keycode == 65361)
		info->look_left = 1;
	if (keycode == 65363)
		info->look_right = 1;
	if (keycode == 65505)
		info->player_speed = 2;
	if (keycode == 65307)
		exit_clean_null(info);
	return (0);
}

int	mouse_rotate(int x, int y, t_mapinfo *info)
{
	(void)y;
	if (x < info->width / 2)
	{
		info->mouse_left = 1;
		info->mouse_right = 0;
	}
	else if (x > info->width / 2)
	{
		info->mouse_left = 0;
		info->mouse_right = 1;
	}
	else
	{
		info->mouse_left = 0;
		info->mouse_right = 0;
	}
	return (0);
}

void	hook_handler(t_mapinfo *info)
{
	mlx_hook(info->data->win, 2, 1L << 0, handle_keydown, info);
	mlx_hook(info->data->win, 3, 1L << 1, handle_keyup, info);
	mlx_hook(info->data->win, 17, 0, exit_clean_null, info);
	mlx_hook(info->data->win, 6, 1L << 6, mouse_rotate, info);
}
