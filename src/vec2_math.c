/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-09 16:21:13 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-09 16:21:13 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"
#include <math.h>

#define M_PI 3.14159265358979323846

double	vec2_magnitude(t_vec2 *vec)
{
	if (!vec)
		return (0);
	return (sqrt(vec->x * vec->x + vec->y * vec->y));
}

t_vec2	vec2_normalise(t_vec2 *vec)
{
	double	mag;

	if (!vec)
		return ((t_vec2){0,0});
	mag = vec2_magnitude(vec);
	return (
		(t_vec2){
			.x = (vec->x / mag),
			.y = (vec->y / mag)
		}
	);
}

t_vec2	vec2_add(t_vec2 *vec1, t_vec2 *vec2)
{
	return ((t_vec2){.x = vec1->x + vec2->x,
			.y = vec1->y + vec2->y});
}
t_vec2	vec2_rotate_euler(t_vec2 *vec, float angle)
{
	t_vec2 rotated;
	float radians;
	radians = angle * (M_PI / 180.0);
	rotated.x = vec->x * cos(radians) - vec->y * sin(radians);
	rotated.y = vec->x * sin(radians) + vec->y * cos(radians);
	return rotated;
}
