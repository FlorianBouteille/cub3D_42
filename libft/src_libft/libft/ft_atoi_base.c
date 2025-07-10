/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:09:39 by mhanarte          #+#    #+#             */
/*   Updated: 2025/07/08 17:03:03 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strc(char *str)
{
	int	j;
	int	k;

	j = 0;
	while (str[j] != 0)
	{
		k = j + 1;
		while (str[k] != 0)
		{
			if (str[j] == str[k])
			{
				return (0);
			}
			k++;
		}
		j++;
	}
	return (1);
}

int	ft_check(char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (0);
		if (base[i] >= 9 && base[i] <= 13)
			return (0);
		i++;
	}
	if (i < 2 || ft_strc(base) == 0)
		return (0);
	return (1);
}

int	ft_in_base(char c, char *base)
{
	int	k;

	k = 0;
	while (base[k] != 0)
	{
		if (base[k] == c)
			return (k);
		k++;
	}
	return (-1);
}

int	ft_comp(char *base)
{
	int	comp;

	comp = 0;
	while (base[comp] != 0)
		comp++;
	return (comp);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	comp;
	int	signe;
	int	res;

	i = 0;
	signe = 1;
	res = 0;
	comp = ft_comp(base);
	if (ft_comp(base) == 0)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 45
		|| str[i] == 43)
	{
		if (str[i] == 45)
			signe = signe * (-1);
		i++;
	}
	while (str[i] != 0 && ft_in_base(str[i], base) >= 0)
	{
		res = res * comp + ft_in_base(str[i], base);
		i++;
	}
	return (res * signe);
}
/*
#include <stdio.h>

int	main(void)
{
	int	res;


	res = ft_atoi_base("    -122", "0123456789");
	printf("%d", res);
}*/
