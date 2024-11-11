/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_text_colour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 15:46:30 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 15:46:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu_lib.h"

uint32_t *mlx_get_pixel(mlx_image_t *img, size_t x, size_t y);


void	set_text_colour(mlx_image_t *img, uint32_t new_col)
{
	size_t	i[2];

	i[0] = 0;
	while (i[0] < img->width)
	{
		i[1] = 0;
		while (i[1] < img->height)
		{
			if (*mlx_get_pixel(img, i[0], i[1]) != 0)
				mlx_put_pixel(img, i[0], i[1], new_col);
			i[1]++;
		}
		i[0]++;
	}
}
