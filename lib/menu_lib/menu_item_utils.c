/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manu_item_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 09:21:37 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 09:21:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This is for packing items into the menu, we need to dynamically resize the menu
 * for each item in it 
 * (max item width + selector width + padding,
 * 	((text height + padding) * items packed) + padding )
 * 
 */

#include "menu_lib.h"

void	_menu_calc_size(t_menu *mnu)
{
	int	count;

	mnu->_size[0] = (PADDING * 3) + mnu->text_size[0] + PADDING + mnu->_largest_width;
	count = ft_lstsize(mnu->items);
	mnu->_size[1] = PADDING + ((PADDING + mnu->text_size[1]) * count);
}

int	append_mnu_item(t_menu *mnu, t_menu_item *item)
{
	int	count;

	if (!mnu || !item)
		return (0);
	count = ft_lstsize(mnu->items);
	count = (PADDING + ((PADDING + mnu->text_size[1]) * count));
	item->pos[0] = (PADDING * 2) + mnu->text_size[0] + mnu->pos[0];
	item->pos[1] = count + mnu->pos[1];
	ft_lstadd_back(&mnu->items, ft_lstnew(item));
	if (!mnu->selected && item->selectable)
		mnu->selected = ft_lstlast(mnu->items);
	item->needs_redraw = 1;
	mnu->needs_redraw = 1;
	redraw_hook(mnu);
	return (1);
}

void _del_btn(t_menu *mnu, t_payload *payload)
{
	if (!mnu || !payload)
		return ;
	if (payload->text)
		free(payload->text);
	if (payload->param_freeable)
		free(payload->param);
	free(payload);
	return ;
}

void _del_spin(t_menu *mnu, t_spinbox *spn)
{
	if (!mnu || !spn)
		return ;
	while (spn->count--)
		_del_btn(mnu, spn->payloads[spn->count]);
	free(spn->payloads);
	free(spn);
}

void	destroy_mnu_items(t_menu *mnu)
{
	t_list		*lst;
	t_menu_item	*item;

	if (!mnu)
		return ;
	lst = mnu->items;
	while (lst)
	{
		item = lst->content;
		if (mnu->mlx && item->img_item)
			mlx_delete_image(mnu->mlx, item->img_item);
		if (item->display_text)
			free(item->display_text);
		if (item->type_hint == BUTTON)
			_del_btn(mnu, item->type.button);
		else if (item->type_hint == SPIN)
			_del_spin(mnu, item->type.spin);
		else if (item->type_hint == TEXT)
			free(item->type.text);
		free(item);
		lst->content = 0;
		lst = lst->next;
	}
	ft_lstclear(&mnu->items, free);
	mnu->items = 0;
	mnu->selected = 0;
}
