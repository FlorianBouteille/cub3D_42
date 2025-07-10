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
		return (ft_printf("Usage : ./cub3D map.cub\n", NULL, 2));
	parsed = parse_map(argv[1]);
	if (!parsed)
		return (printf("Error reading the file\n"), 1);
	info = get_mapinfo(parsed);
	ft_free_tab(parsed);
	// print_mapinfo(info);
	check_mapinfo(info);
	info->data = init_data();
	load_img(info);
	info->wall = get_wall_info(info->map);
	init_img_buffer(info, &info->minimap, info->tiles_x * info->map_scale,
		info->tiles_y * info->map_scale);
	init_img_buffer(info, &info->frame, 2560, 1344);
	// print_wallinfo(info->wall);
	hook_handler(info);
	draw_minimap(info, 0);
	draw_frame(info);
	draw_minimap(info, 1);
	loop(info);
	free_mapinfo(info);
	return (0);
}
