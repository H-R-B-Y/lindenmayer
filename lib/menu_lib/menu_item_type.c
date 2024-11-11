/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_item_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-10 13:01:54 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-10 13:01:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu_lib.h"

t_menu_item	*create_mnu_txt(char *text)
{
	t_menu_item	*output;

	if (!text)
		return (0);
	output = zeroit(malloc(sizeof(t_menu_item)), sizeof(t_menu_item));
	if (!output)
		return (0);
	output->type_hint = TEXT;
	output->type.text = text;
	output->display_text = ft_strdup(output->type.text);
	return (output);
}

t_payload	*create_payload(void (*exec)(void *), char *(*get_text)(void *), void *param)
{
	t_payload	*output;

	if (!exec || !get_text || !param)
		return (0);
	output = zeroit(malloc(sizeof(t_payload)), sizeof(t_payload));
	if (!output)
		return (0);
	output->exec = exec;
	output->get_text = get_text;
	output->param = param;
	output->param_freeable = 0;
	return (output);
}

t_menu_item	*create_mnu_btn(t_payload *payload)
{
	t_menu_item	*output;

	if (!payload)
		return (0);
	output = zeroit(malloc(sizeof(t_menu_item)), sizeof(t_menu_item));
	if (!output)
		return (0);
	output->type_hint = BUTTON;
	output->type.button = payload;
	output->selectable = 1;
	return (output);
}

t_menu_item	*create_mnu_spn(size_t count, t_payload **payloads)
{
	t_menu_item	*output;
	t_spinbox	*spin;

	if (!payloads || !*payloads)
		return (0);
	output = zeroit(malloc(sizeof(t_menu_item)), sizeof(t_menu_item));
	if (!output)
		return (0);
	output->type_hint = SPIN;
	spin = zeroit(malloc(sizeof(t_spinbox)), sizeof(t_spinbox)); 
	if (!spin)
		return (free(output), (void *)0);
	output->type.spin = spin;
	spin->count = count;
	spin->payloads = payloads;
	output->selectable = 1;
	return (output);
}
