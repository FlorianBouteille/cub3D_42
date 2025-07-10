/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:08:53 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/07 16:26:59 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	my_pixel_put(t_img_buffer *img_buffer, int x, int y, int color)
{
	char *dst = img_buffer->addr + (y * img_buffer->line_length + x
			* (img_buffer->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}