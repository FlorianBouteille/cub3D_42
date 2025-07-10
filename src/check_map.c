/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:14 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/07 16:32:53 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     get_map_width(char **map)
{
    int max_len;
    int i;

    max_len = 0;
    i = 0;
    while (map[i])
    {
        if (ft_strlen(map[i]) > max_len)
            max_len = ft_strlen(map[i]);
        i++;
    }
    return (max_len);
}

int     get_map_height(char **map)
{
    int i;

    i = 0;
    while (map[i])
        i++;
    return (i);
}
void    check_characters(t_mapinfo *info)
{
    int i;
    int j;
    int count_players;

    i = 0;
    count_players = 0;
    while (info->map[i])
    {
        j = 0;
        while (info->map[i][j])
        {
            if (!ft_strchr("01 NSWE\n", info->map[i][j]))
                exit_clean("Wrong caracter found", info, NULL);       
            if (ft_strchr("NSEW", info->map[i][j]))
                count_players++;
            j++;
        }
        i++;
    }
    if (count_players != 1)
        exit_clean("Wrong number of players", info, NULL);
}
void    check_map(t_mapinfo *info)
{
    if (!(info->map))
        exit_clean("No map found !", info, NULL);
    check_characters(info);
    if (!check_walls(info->map, info))
        exit_clean("Map must be closed by walls", info, NULL);
}