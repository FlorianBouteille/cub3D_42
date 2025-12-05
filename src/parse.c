/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:15:03 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 16:07:30 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_info(t_mapinfo *info, char *line, int *non_empty_lines)
{
	char	c;

	c = check_line(line);
	while (c != 'F' && c != 'C' && *line && *line != ' ')
		line++;
	if (c == 'N' && !info->north->path)
		info->north->path = ft_strdup(line);
	if (c == 'S' && !info->south->path)
		info->south->path = ft_strdup(line);
	if (c == 'E' && !info->east->path)
		info->east->path = ft_strdup(line);
	if (c == 'W' && !info->west->path)
		info->west->path = ft_strdup(line);
	if (c == 'F' && !info->floor_color)
		info->floor_color = ft_strdup(line);
	if (c == 'C' && !info->ceiling_color)
		info->ceiling_color = ft_strdup(line);
	if (c != 0)
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
			exit_clean("Error\nInvalid characters", info, parsed_info);
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
		exit_clean("Error\nCopy map Failed", info, parsed_info);
	i = 0;
	while (parsed[i] && parsed[i][0] != '\n')
	{
		map[i] = ft_strdup(parsed[i]);
		if (!map[i])
			exit_clean("Error\nCopy map Failed", info, parsed_info);
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
	if (non_empty_lines != 6)
		exit_clean("Error\nWrong map information\n", info, parsed);
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
		free(parsed);
		return (NULL);
	}
	while (parsed[i++])
		parsed[i] = get_next_line(fd);
	parsed[i] = NULL;
	return (parsed);
}
