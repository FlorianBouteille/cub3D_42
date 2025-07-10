#include "cub3D.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf(tab[i], BOLD BLUE, 1);
		i++;
	}
}
// void    print_color(t_color *color)
// {
//     printf("Red : ");
//     printf("%i\n", color->red);
//     printf("Green ");
//     printf("%i\n", color->green);
//     printf("Blue : ");
//     printf("%i\n", color->blue);
// }

void	print_mapinfo(t_mapinfo *info)
{
	printf("NO = %s\n", (char *)info->north);
	printf("SO = %s\n", (char *)info->south);
	printf("WE = %s\n", (char *)info->west);
	printf("EA = %s\n", (char *)info->east);
	printf("Floor = %s\n", info->floor_color);
	printf("Ceiling = %s\n", info->ceiling_color);
	print_tab(info->map);
}

void	print_wallinfo(t_wallinfo *wall)
{
	t_wallinfo *tmp;

	tmp = wall;
	while (tmp)
	{
		printf("wall in [%d][%d]\n", tmp->y, tmp->x);
		tmp = tmp->next;
	}
}