/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-10 10:37:47 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-10 10:37:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_LIB_H
# define MENU_LIB_H

# include "MLX42.h"
# include "libft.h"
# define PADDING 5

typedef struct s_payload // Not sure what the payload will need.
{
	char	*text;
	void	(*exec)(void *);
	char	*(*get_text)(void *);
	void	*param;
	int		param_freeable;
}	t_payload;

typedef struct s_spinbox
{
	t_payload	**payloads;
	size_t		count;
	size_t		index;
}	t_spinbox;

typedef enum e_type
{
	TEXT, BUTTON, SPIN
}	t_item_type;

typedef struct s_menu_item
{
	mlx_image_t	*img_item;
	char		*display_text; 
	int			needs_redraw;
	int			selectable;
	size_t		pos[2];
	t_item_type	type_hint;
	union {
		t_spinbox	*spin;
		t_payload	*button;
		char		*text;
	}			type;
}	t_menu_item;

typedef struct s_menu
{
	size_t		pos[2];
	mlx_t		*mlx;
	int			enabled;
	mlx_image_t	*bg_img;
	size_t		_size[2];
	size_t		text_size[2];
	t_list		*items;
	mlx_image_t	*selector;
	t_list		*selected;
	uint32_t	bg;
	int			needs_redraw;
	size_t		_largest_width;
	int			startdepth;
}	t_menu;

/**
 * @brief create a new menu.
 */
t_menu		*create_menu(mlx_t *mlx, size_t pos[2]);

/**
 * @brief Destory a menu.
 */
void		destroy_menu(t_menu *mnu);

/**
 * @brief Disable a menu.
 */
void		disable_menu(t_menu *mnu);

/**
 * @brief Enable a menu.
 */
void		enable_menu(t_menu *mnu);

/**
 * @brief append a new item to the menu.
 */
int			append_mnu_item(t_menu *mnu, t_menu_item *item);

/**
 * @brief delete and free all menu items
 * 
 * menu items will be deleted:
 * 	text is freed.
 * 	payload text is free'd but param is not.
 * 	spin before is freed and payloads are free'd like buttons.
 */
void		destroy_mnu_items(t_menu *mnu);

/**
 * Create a new menu text item.
 */
t_menu_item	*create_mnu_txt(char *text);

/**
 * Create a new menu payload.
 */
t_payload	*create_payload(void (*exec)(void *), char *(*get_text)(void *), void *param);

/**
 * @brief Create a new menu button.
 */
t_menu_item	*create_mnu_btn(t_payload *payload);

/**
 * @brief Create a new menu spinner.
 */
t_menu_item	*create_mnu_spn(size_t count, t_payload **payload);

/**
 * @brief MLX keyhook for menu navigation.
 */
void	menu_nav_hook(mlx_key_data_t keydata, void* param);

/**
 * @brief MLX loop hook for redrawing when needed.
 */
void	redraw_hook(void *param);

/**
 * @brief Redraw a menu item
 */
void	redraw_item(t_menu *mnu, t_menu_item *item);

/**
 * @brief Redraw the selector
 */
void	redraw_selector(t_menu *mnu);

#endif
