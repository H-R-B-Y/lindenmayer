/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_nav_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-10 13:41:48 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-10 13:41:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu_lib.h"

void	_menu_spin_item(t_menu *mnu, t_menu_item *item, int dir)
{
	t_spinbox	*payload;
	if (!mnu || !item || item->type_hint != SPIN)
		return;
	payload = item->type.spin;
	if (dir == -1 && payload->index == 0)
		payload->index = payload->count - 1;
	else
		payload->index = (payload->index + dir) % payload->count;
	item->needs_redraw = 1;
}

void	_nav_manu_action(t_menu_item *item)
{
	t_payload	*payload;
	char		*tmp;

	if (!item)
		return ;
	if (item->type_hint == BUTTON)
		payload = item->type.button;
	else if (item->type_hint == SPIN)
		payload = item->type.spin->payloads[item->type.spin->index];
	payload->exec(payload->param);
	tmp = payload->get_text(payload->param);
	free(item->display_text);
	item->display_text = tmp;
	item->needs_redraw = 1;
}

t_list *_get_next_selected(t_menu *mnu)
{
	t_list	*lst;

	if (!mnu)
		return (0);
	lst = mnu->selected;
	if (!mnu->selected)
		lst = mnu->items;
	if (!mnu->items)
		return (0);
	lst = lst->next;
	while (lst)
	{
		if (((t_menu_item *)lst->content)->selectable)
			return (lst);
		lst = lst->next;
	}
	mnu->selected = mnu->items;
	return (_get_next_selected(mnu));
}
t_list *_get_prev_selected(t_menu *mnu)
{
	t_list	*lst;
	t_list	*prev;

	if (!mnu)
		return (0);
	lst = mnu->items;
	prev = 0;
	while (lst)
	{
		if (lst != mnu->selected && ((t_menu_item *)lst->content)->selectable)
			prev = lst;
		else if (lst == mnu->selected && prev != 0)
			return (prev);
		if (lst->next == 0 && prev != 0)
			return (prev);
		lst = lst->next;
	}
	return (0);
}

void	menu_nav_hook(mlx_key_data_t keydata, void* param)
{
	t_menu	*mnu;

	if (!param)
		return ;
	mnu = param;
	if (!mnu->enabled || !mnu->selected)
		return ;
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_RELEASE)
		_nav_manu_action(mnu->selected->content);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		mnu->selected = _get_prev_selected(mnu);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		mnu->selected = _get_next_selected(mnu);
	else if (mnu->selected && ((t_menu_item *)mnu->selected->content)->type_hint == SPIN)
	{
		if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
			_menu_spin_item(mnu, mnu->selected->content, -1);
		else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
			_menu_spin_item(mnu, mnu->selected->content, 1);
	}
		
	
}
