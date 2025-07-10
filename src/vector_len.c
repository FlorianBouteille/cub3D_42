/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:10:34 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/07 14:19:32 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


float square(float a)
{
    return (a * a);
}
float   get_vector_len(float x1, float y1, float x2, float y2)
{
    float   len;

    len = sqrtf(square(x2 - x1) + square(y2 - y1));
    return (len);
}