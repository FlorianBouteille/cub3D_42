/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:35 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 15:11:24 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_extension(char *filename)
{
	int	index;

	index = ft_strlen(filename) - 4;
	if (index < 1)
		return (-1);
	return (ft_strcmp(filename + index, ".cub"));
}

int	main(int argc, char **argv)
{
	char		**parsed;
	t_mapinfo	*info;

	if (argc != 2 || check_extension(argv[1]) != 0)
		return (ft_printf("Error\nUsage : ./cub3D map.cub\n", NULL, 2));
	parsed = parse_map(argv[1]);
	if (!parsed)
		return (printf("Error\nCouldn't read file\n"), 1);
	info = get_mapinfo(parsed);
	ft_free_tab(parsed);
	check_mapinfo(info);
	info->data = init_data(info);
	load_img(info);
	init_img_buffer(info, &info->minimap, info->tiles_x * info->map_scale,
		info->tiles_y * info->map_scale);
	init_img_buffer(info, &info->frame, info->width, info->height);
	hook_handler(info);
	draw_minimap(info, 0);
	draw_frame(info);
	loop(info);
	free_mapinfo(info);
	return (0);
}
