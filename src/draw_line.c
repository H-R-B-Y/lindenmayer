/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 17:42:01 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-07 17:42:01 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"
#include <math.h>

void	_draw_point(mlx_image_t *img,
			t_vec2 center, float thickness,
			uint32_t colour)
{
	int	radius = thickness / 2;
	int	dx[2];

	dx[0] = -radius;
	while (dx[0] <= radius)
	{
		dx[1] = -radius;
		while(dx[1] <= radius)
		{
			dx[1]++;
			if ((dx[0] * dx[0]) + (dx[1] * dx[1]) <= radius * radius)
				if ((center.x + dx[0]) < img->width && (center.y + dx[1]) < img->height
					&& (center.x + dx[0]) > 0 && (center.y + dx[1]) > 0)
					mlx_put_pixel(img, (center.x + dx[0]), (center.y + dx[1]), colour);
		}
		dx[0]++;
	}
}

void	_put_proto(t_lin *model,
			t_ln_proto *proto,
			t_vec2 point[3])
{
	uint32_t	colour;

	if (!model || !proto || !point)
		return;
	if (proto->c_type == FUNC)
		colour = proto->c_val.func(model, point, proto->param);
	else if (proto->c_type == GRAD)
		colour = 0xFFF;
	else
		colour = proto->c_val.stat;
	_draw_point(model->canvas, point[1], proto->thickness, colour);
}

void	draw_line(t_vec2 start,
		t_vec2 end,
		t_lin *model,
		t_ln_proto *proto)
{
	t_vec2	d;
	t_vec2	s;
	double err;
	double e2;
	t_vec2 sp;

	sp = start;
	d = (t_vec2){abs(end.x - start.x), abs(end.y - start.y)};
	s = (t_vec2){(start.x < end.x) ? 1 : -1, (start.y < end.y) ? 1 : -1};
	err = d.x - d.y;
	while (1) {
		if (abs(start.x - end.x) < 1 && abs(start.y - end.y) < 1)
			break;
		if (start.x < model->canvas->width && start.y < model->canvas->height
			&& start.x >= 1 && start.y >= 1)
			_put_proto(model, proto, (t_vec2[3]){sp, start, end});
		e2 = 2 * err;
		err -= (d.y * (e2 > -d.y));
		start.x += (s.x * (e2 > -d.y));
		err += (d.x * (e2 < d.x));
		start.y += (s.y * (e2 < d.x));
	}
}
