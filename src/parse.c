#include "cub3D.h"

int	count_lines(char *file)
{
	int		i;
	int		fd;
	char	*line;

	i = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}
// t_color *get_color(char *info)
// {
//     t_color *color;
//     int i;

//     if (check_color(info) != 2)
//         return (NULL);
//     color = malloc(sizeof(t_color));
//     if (!color)
//         return (NULL);
//     i = 0;
//     while (info[i] && !ft_isdigit(info[i]))
//         i++;
//     color->red = ft_atoi(info + i);
//     while (info[i] && ft_isdigit(info[i]))
//         i++;
//     i++;
//     color->green = ft_atoi(info + i);
//     while (info[i] && ft_isdigit(info[i]))
//         i++;
//     i++;
//     color->blue = ft_atoi(info + i);
//     while (info[i] && ft_isdigit(info[i]))
//         i++;
//     if (info[i] && info[i] != '\n')
//         return (NULL);
//     return (color);
// }

void	fill_info(t_mapinfo *info, char *line, int *non_empty_lines)
{
	if (*non_empty_lines == 0)
		info->north->path = ft_strdup(line);
	else if (*non_empty_lines == 1)
		info->south->path = ft_strdup(line);
	else if (*non_empty_lines == 2)
		info->west->path = ft_strdup(line);
	else if (*non_empty_lines == 3)
		info->east->path = ft_strdup(line);
	else if (*non_empty_lines == 4)
		info->floor_color = ft_strdup(line);
	else if (*non_empty_lines == 5)
		info->ceiling_color = ft_strdup(line);
	(*non_empty_lines)++;
}

void	check_endfile(t_mapinfo *info, char **parsed, char **parsed_info,
		char **map)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (ft_strlen(parsed[i]) > 1 || parsed[i][0] != '\n')
        {
            ft_free_tab(map);
			exit_clean("Invalid characters found after map", info, parsed_info);
        }
		i++;
	}
}
char	**copy_map(char **parsed, t_mapinfo *info, char **parsed_info)
{
	char	**map;
	int		i;

	i = 0;
	while (parsed[i] && parsed[i][0] != '\n')
		i++;
	map = (char **)malloc((i + 1) * sizeof(char *));
	if (!map)
		exit_clean("Copy map Failed", info, parsed_info);
	i = 0;
	while (parsed[i] && parsed[i][0] != '\n')
	{
		map[i] = ft_strdup(parsed[i]);
		if (!map[i])
			exit_clean("Copy map Failed", info, parsed_info);
		i++;
	}
	map[i] = NULL;
	check_endfile(info, parsed + i, parsed_info, map);
	return (map);
}
t_mapinfo	*get_mapinfo(char **parsed)
{
	t_mapinfo	*info;
	int			i;
	int			non_empty_lines;

	i = 0;
	non_empty_lines = 0;
	info = init_mapinfo();
	if (!info)
		return (NULL);
	while (parsed[i] && non_empty_lines < 6)
	{
		if (parsed[i][0] != '\n')
			fill_info(info, parsed[i], &non_empty_lines);
		i++;
	}
	while (parsed[i] && parsed[i][0] == '\n')
		i++;
	info->map = copy_map(parsed + i, info, parsed);
	return (info);
}
char	**parse_map(char *file)
{
	char	**parsed;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	parsed = (char **)malloc((count_lines(file) + 1) * sizeof(char *));
	if (!parsed)
		return (close(fd), NULL);
	i = 0;
	parsed[i] = get_next_line(fd);
    if (!parsed[i])
    {
        parsed[i] = NULL;
        return (parsed);
    }
	while (parsed[i++])
		parsed[i] = get_next_line(fd);
	parsed[i] = NULL;
	return (parsed);
}
