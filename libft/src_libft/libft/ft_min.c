/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:48:02 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/09 14:50:19 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float ft_min(float a, float b)
{
    if (a > b)
        return (b);
    return (a); 
}

float ft_max(float a, float b)
{
    if (a > b)
        return (a);
    return (b);
}