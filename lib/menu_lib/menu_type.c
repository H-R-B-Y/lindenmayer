/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-10 12:23:49 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-10 12:23:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu_lib.h"

void	_menu_draw_bg(t_menu *mnu)
{
	size_t index[2];

	index[0] = 0;
	while (index[0] < mnu->bg_img->width)
	{
		index[1] = 0;
		while (index[1] < mnu->bg_img->height)
		{
			mlx_put_pixel(mnu->bg_img, index[0], index[1], mnu->bg);
			index[1]++;
		}
		index[0]++;
	}
}

t_menu	*create_menu(mlx_t *mlx, size_t pos[2])
{
	t_menu	*output;

	if (!mlx)
		return (0);
	output = zeroit(malloc(sizeof(t_menu)), sizeof(t_menu));
	if (!output)
		return (0);
	output->mlx = mlx;
	output->selector = mlx_put_string(mlx, ">", pos[0], pos[1]);
	output->text_size[0] = output->selector->width;
	output->text_size[1] = output->selector->height;
	output->bg_img = mlx_new_image(mlx, output->text_size[0], output->text_size[1]);
	mlx_image_to_window(mlx, output->bg_img, pos[0], pos[1]);
	output->bg_img->instances[0].enabled = 0;
	output->_size[0] = 10;
	output->_size[1] = 10;
	output->pos[0] = pos[0];
	output->pos[1] = pos[1];
	output->fg = 0xFFFFFFFF;
	output->selector->instances[0].enabled = 0;
	return (output);
}

void	destroy_menu(t_menu *mnu)
{
	if (mnu->bg_img)
		mlx_delete_image(mnu->mlx, mnu->bg_img);
	if (mnu->selector)
		mlx_delete_image(mnu->mlx, mnu->selector);
	if (mnu->items)
		destroy_mnu_items(mnu);
	free(mnu);
}

void disable_menu(t_menu *mnu)
{
	t_list		*lst;
	t_menu_item	*item;

	mnu->enabled = 0;
	mnu->bg_img->instances[0].enabled = 0;
	mnu->selector->instances[0].enabled = 0;
	lst = mnu->items;
	while (lst)
	{
		item = lst->content;
		item->img_item->instances[0].enabled = 0;
		lst = lst->next;
	}
}

void enable_menu(t_menu *mnu)
{
	t_list		*lst;
	t_menu_item	*item;

	mnu->enabled = 1;
	mnu->bg_img->instances[0].enabled = 1;
	mnu->selector->instances[0].enabled = 1;
	lst = mnu->items;
	while (lst)
	{
		item = lst->content;
		item->img_item->instances[0].enabled = 1;
		lst = lst->next;
	}
}
