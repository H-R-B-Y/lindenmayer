/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-10 10:27:11 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-10 10:27:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"

void	draw_hook(void *param)
{
	t_lin *p;
	char *start;

	p = param;
	p->timer += p->mlx->delta_time;
	start = &(p->model[p->index]);
	if (p->timer > p->delay && p->model[p->index])
	{
		while (p->model[p->index] && &(p->model[p->index]) - start < p->dc)
			do_draw(p, p->model[p->index++]);
		p->timer = 0;
	}
}

void	lin_key_hook(mlx_key_data_t keydata, void* param)
{
	t_lin	*lin;

	lin = param;
	if (keydata.key == MLX_KEY_LEFT_BRACKET && keydata.action == MLX_RELEASE
		&& ++lin->needs_redraw)
		lin->scale -= 0.1;
	if (keydata.key == MLX_KEY_RIGHT_BRACKET && keydata.action == MLX_RELEASE
		&& ++lin->needs_redraw)
		lin->scale += 0.1;
	if (keydata.key == MLX_KEY_S
		&& ++lin->needs_redraw)
		lin->offset.y += (lin->canvas->height / 100);
	if (keydata.key == MLX_KEY_A
		&& ++lin->needs_redraw)
		lin->offset.x -= (lin->canvas->width / 100);
	if (keydata.key == MLX_KEY_W
		&& ++lin->needs_redraw)
		lin->offset.y -= (lin->canvas->height / 100);
	if (keydata.key == MLX_KEY_D
		&& ++lin->needs_redraw)
		lin->offset.x += (lin->canvas->width / 100);
}

void	lin_redraw(void *param)
{
	t_vec2 size;
	t_lin *p;

	p = param;
	size = (t_vec2){.x=p->canvas->width,.y=p->canvas->height};
	if (!p->needs_redraw)
		return ;
	mlx_delete_image(p->mlx, p->canvas);
	p->canvas = mlx_new_image(p->mlx, p->mlx->width, p->mlx->height);
	mlx_image_to_window(p->mlx, p->canvas, 0, 0);
	if (size.x != p->mlx->width || size.y != p->mlx->height)
		p->offset = (t_vec2){.x = p->mlx->width / 2, .y = p->mlx->height / 2};
	p->cursor->pos = (t_vec2){0,0};
	p->cursor->dir = (t_vec2){0,1};
	p->index = 0;
	p->timer = 0;
	p->needs_redraw = 0;
}
