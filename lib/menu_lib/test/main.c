/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 10:19:31 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-11 10:19:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/menu_lib.h"
#include <stdio.h>

void prnt(void *r)
{
	printf((char *)r);
	printf("\n");
	fflush(stdout);
}

char *get_txt(void *r)
{
	return (ft_strdup(r));
}

static inline char *delete_txt(void *r)
{
	(void)r;
	return (ft_strdup("DESTROY!"));
}

static inline void terminate(void *r)
{
	mlx_close_window(r);
}

int main ()
{
	mlx_t *mlx = mlx_init(1920, 1080, "Lindenmayer", 1);
	t_menu *mnu = create_menu(mlx, (size_t[2]){100,100});
	mnu->bg = 0x0000001F;
	mnu->startdepth = 2;
	mnu->enabled = 1;

	t_menu_item *txt1 = create_mnu_txt(ft_strdup("HELLO WORLD"));
	append_mnu_item(mnu, txt1);

	t_payload	*tst1 = create_payload(prnt, get_txt, "LOL");
	t_menu_item *button1 = create_mnu_btn(tst1);
	append_mnu_item(mnu, button1);

	t_payload	*tst2 = create_payload(prnt, get_txt, "LOL2");
	t_menu_item *button2 = create_mnu_btn(tst2);
	append_mnu_item(mnu, button2);

	t_payload **spin1 = malloc(sizeof(t_payload *) * 3);
	spin1[0] = create_payload(prnt, get_txt, "LOL3");
	spin1[1] = create_payload(terminate, delete_txt, mlx);
	spin1[2] = create_payload(prnt, get_txt, "LOL4");
	t_menu_item *spinner1 = create_mnu_spn(3, spin1);
	append_mnu_item(mnu, spinner1);

	mlx_key_hook(mlx, menu_nav_hook, mnu);
	mlx_loop_hook(mlx, redraw_hook, mnu);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	destroy_menu(mnu);
	return (0);
}
