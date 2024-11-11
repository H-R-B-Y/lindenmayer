/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 17:09:58 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-07 17:09:58 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"

#include <stdio.h>


t_lin	*init_linden(mlx_t *mlx)
{
	t_lin *out;

	out = zeroit(malloc(sizeof(t_lin)), sizeof(t_lin));
	if (!out)
		return (0);
	out->mlx = mlx;
	out->canvas = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!out->canvas)
		return (free(out), (void *)0);
	mlx_image_to_window(mlx, out->canvas, 0, 0);
	out->offset = (t_vec2){mlx->width / 2, mlx->height / 2};
	out->cursor = zeroit(malloc(sizeof(t_cur)), sizeof(t_cur));
	if (!out->cursor)
		return (mlx_delete_image(mlx, out->canvas), free(out), (void *)0);
	out->cursor->dir = (t_vec2){.y = 1, .x = 0};
	out->scale = 1;
	out->index = 0;
	out->timer = 1;
	out->dc = 100;
	out->delay = 0.00;
	return (out);
}

void	del_linden(t_lin *lin)
{
	if (lin->canvas)
		mlx_delete_image(lin->mlx, lin->canvas);
	if (lin->rules)
		ft_lstclear(&lin->rules, free);
	if (lin->draw)
		ft_lstclear(&lin->draw, free);
	if (lin->model)
		free(lin->model);
	if (lin->line)
		free(lin->line);
	free(lin->cursor);
	free(lin);
}



int main(int argc, char **argv)
{
	mlx_t *mlx = mlx_init(1920, 1080, "Lindenmayer", 1);
	mlx_image_t *img = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_image_to_window(mlx, img, 0, 0);

	t_lin *master = init_linden(mlx);

	master->line = malloc(sizeof(t_ln_proto));
	*(t_ln_proto *)master->line = (t_ln_proto){
		.c_type = STAT,
		.thickness = 3,
		.c_val.stat = 0x00FF,
		.param = 0};

	append_c_rule(master, 'p', "ppfp");
	append_c_rule(master, 'f', "pap");
	append_c_rule(master, 'a', "fap");
	append_d_rule(master, 'p', default_draw, (union u_param){.mag = 30});
	append_d_rule(master, 'f', default_rotate, (union u_param){.euler = -48});
	append_d_rule(master, 'a', default_rotate, (union u_param){.euler = 24});
	master->model = prop(master, "p", 8);
	printf("test: %s", master->model);
	fflush(stdout);

	mlx_loop_hook(mlx, draw_hook, master);
	mlx_loop_hook(mlx, lin_redraw, master);
	mlx_key_hook(mlx, lin_key_hook, master);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	del_linden(master);
	return (0);
}
