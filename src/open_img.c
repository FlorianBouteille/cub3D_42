/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:18:39 by mhanarte          #+#    #+#             */
/*   Updated: 2025/07/10 17:30:11 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_color_array(int **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("symbol = %d, color = %X\n", array[i][0], array[i][1]);
		i++;
	}
}
int	get_texture_height(char *line)
{
	int	i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	return (ft_atoi(line + i));
}

int	get_texture_width(char *line)
{
	int	i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	return (ft_atoi(line + i));
}

int	get_numbers_of_colors(char *line)
{
	int	i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	return (ft_atoi(line + i));
}

int	get_right_color(char c, int **char_colors)
{
	int	i;

	i = 0;
	while (char_colors[i][0] != -1 && char_colors[i][1] != -1)
	{
		if (char_colors[i][0] == (int)c)
			return (char_colors[i][1]);
		i++;
	}
	return (-1);
}

void	set_up_img_dimension(t_mapinfo *info, int direction, int width,
		int height)
{
	if (direction == NO)
	{
		info->north->height = height;
		info->north->width = width;
	}
	if (direction == SO)
	{
		info->south->height = height;
		info->south->width = width;
	}
	if (direction == EA)
	{
		info->east->height = height;
		info->east->width = width;
	}
	if (direction == WE)
	{
		info->west->height = height;
		info->west->width = width;
	}
}

int	*build_texture(t_mapinfo *info, int **char_colors, char **file,
		int direction)
{
	int	i;
	int	j;
	int	k;
	int	height;
	int	width;
	int	*colors;

	k = 0;
	i = 0;
	while (file[i][0] != '\"')
		i++;
	width = get_texture_width(file[i]);
	height = get_texture_height(file[i]);
	set_up_img_dimension(info, direction, width, height);
	colors = malloc(width * height * sizeof(int));
	if (!colors)
		exit_clean("failed to alloc texture array", info, NULL);
	while (k < get_numbers_of_colors(file[i]))
		k++;
	i += k + 1;
	k = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j + 1] && j < width)
		{
			colors[k * width + j] = get_right_color(file[i][j + 1],
					char_colors);
			if (colors[k * width + j] == -1)
			{
				free(colors);
				ft_free_int_tab(char_colors);
				ft_free_tab(file);
				exit_clean("Wrong caracter found in texture", info, NULL);
			}
			j++;
		}
		k++;
		i++;
	}
	ft_free_int_tab(char_colors);
	ft_free_tab(file);
	return (colors);
}

int	*fill_colors_array(t_mapinfo *info, char *texture, int direction)
{
	char	**file;
	int		i;
	int		j;
	int		**char_colors;

	j = 0;
	i = 0;
	file = parse_map(texture);
	while (file[i] && file[i][0] != '\"')
		i++;
	char_colors = malloc(sizeof(int *) * (get_numbers_of_colors(file[i]) + 1));
	if (!char_colors)
		exit_clean("failed to alloc color array", info, NULL);
	while (j < get_numbers_of_colors(file[i]) + 1)
	{
		char_colors[j] = malloc(sizeof(int) * 2);
		char_colors[j][0] = 0;
		char_colors[j][1] = 0;
		j++;
	}
	char_colors[j - 1][0] = -1;
	char_colors[j - 1][1] = -1;
	j = 0;
	while (j < get_numbers_of_colors(file[i]))
	{
		char_colors[j][0] = file[i + j + 1][1];
		if (!ft_strchr(file[i + j + 1], '#'))
		{
			ft_free_tab(file);
			ft_free_int_tab(char_colors);
			free(texture);
			exit_clean("Wrong color found, we accept only #Hexadecimal form\n",
				info, NULL);
		}
		char_colors[j][1] = ft_atoi_base(ft_strchr(file[i + j + 1], '#') + 1,
				"0123456789ABCDEF");
		j++;
	}
	free(texture);
	return (build_texture(info, char_colors, file, direction));
}

void	*safe_xpm_to_img(void *mlx, char *path, t_mapinfo *info)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
	{
		ft_putstr_fd("Error, impossible to load : ", 2);
		ft_putstr_fd(path, 2);
		free(path);
		exit_clean("\n", info, NULL);
	}
	free(path);
	return (img);
}

void	load_img(t_mapinfo *info)
{
	info->north->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->north->path + 3, "\n"), info);
	info->north->pixels = fill_colors_array(info,
			ft_strtrim((char *)info->north->path + 3, "\n"), NO);
	info->south->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->south->path + 3, "\n"), info);
	info->south->pixels = fill_colors_array(info,
			ft_strtrim((char *)info->south->path + 3, "\n"), SO);
	info->east->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->east->path + 3, "\n"), info);
	info->east->pixels = fill_colors_array(info,
			ft_strtrim((char *)info->east->path + 3, "\n"), EA);
	info->west->img = safe_xpm_to_img(info->data->mlx,
			ft_strtrim((char *)info->west->path + 3, "\n"), info);
	info->west->pixels = fill_colors_array(info,
			ft_strtrim((char *)info->west->path + 3, "\n"), WE);
}
