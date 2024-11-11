/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_redraw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 09:50:44 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 09:50:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu_lib.h"

void	_menu_draw_bg(t_menu *mnu);
void	_menu_calc_size(t_menu *mnu);
void	set_text_colour(mlx_image_t *img, uint32_t new_col);

void	redraw_selector(t_menu *mnu)
{
	t_menu_item	*item;

	if (!mnu->selected)
		return ;
	if (!mnu->selector)
		mnu->selector = mlx_put_string(mnu->mlx, ">", 0, 0);
	item = mnu->selected->content;
	mnu->selector->instances[0].enabled = 1;
	mnu->selector->instances[0].x = (item->pos[0]
			- (PADDING + mnu->text_size[0]));
	mnu->selector->instances[0].y = item->pos[1];
	mlx_set_instance_depth(&mnu->selector->instances[0], mnu->startdepth + 2);
}

void	redraw_item(t_menu *mnu, t_menu_item *item)
{
	free(item->display_text);
	if (item->type_hint == BUTTON)
		item->display_text = item->type.button
			->get_text(item->type.button->param);
	else if (item->type_hint == SPIN)
		item->display_text = item->type.spin->payloads[item->type.spin->index]
			->get_text(item->type.spin->payloads[item->type.spin->index]
				->param);
	else
		item->display_text = ft_strdup(item->type.text);
	if (item->img_item)
		mlx_delete_image(mnu->mlx, item->img_item);
	item->img_item = mlx_put_string(mnu->mlx, item->display_text,
		item->pos[0], item->pos[1]);
	mlx_set_instance_depth(&item->img_item->instances[0],
		mnu->startdepth + 1);
	if (item->img_item->width > mnu->_largest_width)
	{
		mnu->_largest_width = item->img_item->width;
		mnu->needs_redraw = 1;
	}
	item->needs_redraw = 0;
}

void	_redraw_bg(t_menu *mnu)
{
	if (mnu->bg_img)
		mlx_delete_image(mnu->mlx, mnu->bg_img);
	_menu_calc_size(mnu);
	mnu->bg_img = mlx_new_image(mnu->mlx, mnu->_size[0], mnu->_size[1]);
	mlx_image_to_window(mnu->mlx, mnu->bg_img, mnu->pos[0], mnu->pos[1]);
	_menu_draw_bg(mnu);
	mlx_set_instance_depth(&mnu->bg_img->instances[0], mnu->startdepth + 0);
	mnu->needs_redraw = 0;
}

void	redraw_hook(void *param)
{
	t_menu	*mnu;
	t_list	*lst;

	if (!param)
		return ;
	mnu = param;
	if (!mnu->enabled)
		return ;
	if (mnu->needs_redraw)
		_redraw_bg(mnu);
	lst = mnu->items;
	while (lst)
	{
		if ((t_menu_item *)lst->content && ((t_menu_item *)lst->content)->needs_redraw)
			redraw_item(mnu, (t_menu_item *)lst->content);
		lst = lst->next;
	}
	redraw_selector(mnu);
}
