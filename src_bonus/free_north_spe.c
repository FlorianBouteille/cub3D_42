/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_north_spe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:28:34 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 16:31:37 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_north_and_exit(t_mapinfo *info, char *msg)
{
	if (info->north)
		free_texture(info, info->north);
	exit_clean(msg, info, NULL);
}
