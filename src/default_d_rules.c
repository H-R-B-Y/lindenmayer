/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-09 16:17:17 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-09 16:17:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"

void	default_draw(t_lin *master, union u_param param)
{
	t_vec2	start;
	t_vec2	end;

	start = master->cursor->pos;
	end = vec2_normalise(&master->cursor->dir);
	end.x *= (param.mag * master->scale);
	end.y *= (param.mag * master->scale);
	end = vec2_add(&end, &start);
	master->cursor->pos = end;
	draw_line(vec2_add(&start, &master->offset),
		vec2_add(&end, &master->offset), master, master->line);
}

void	default_rotate(t_lin *master, union u_param param)
{
	t_vec2	dir;
	
	dir = master->cursor->dir;
	master->cursor->dir = vec2_rotate_euler(&dir, param.euler);
}


