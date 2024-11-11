/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 16:10:37 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 16:10:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lindenmayer.h"

t_menu	init_menu(mlx_t *mlx, t_lin *lin)
{
	t_menu *mnu;
	t_menu *mnu = create_menu(mlx, (size_t[2]){100,100});
	mnu->bg = 0x0000001F;
	mnu->startdepth = 2;
	mnu->enabled = 1;

}