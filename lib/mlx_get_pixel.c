/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 15:35:59 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 15:35:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/MLX42.h"

uint32_t *mlx_get_pixel(mlx_image_t *img, size_t x, size_t y)
{
	if (!img || x > img->width || y > img->height)
		return (0);
	return ((void *)(&img->pixels[(y * img->width + x) * sizeof(int32_t)]));
}
