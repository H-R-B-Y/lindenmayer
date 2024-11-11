/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lindenmayer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 16:53:19 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-07 16:53:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINDENMAYER_H
# define LINDENMAYER_H

# include "../include/libft.h"
# include "../include/MLX42.h"
# include "../include/menu_lib.h"

# include <stdlib.h>

typedef struct s_lin	t_lin;
typedef struct s_cur	t_cur;

/**
 * It's a 2D vector, say less.
 */
typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

// ██████  ██    ██ ██      ███████ ███████ 
// ██   ██ ██    ██ ██      ██      ██      
// ██████  ██    ██ ██      █████   ███████ 
// ██   ██ ██    ██ ██      ██           ██ 
// ██   ██  ██████  ███████ ███████ ███████ 

/**
 * @brief Character rule
 * @param key the lookup key for the rule.
 * @param rule the resolved string value.
 * 
 * A character rule represents how the prop function
 * will resolve a given character in the seed, the resulting
 * rule string is appended to the end of the current prop.
 * Example: 
 * .key = 'p'
 * .rule = "pfp"
 * With a seed of "pp" will result in the prop "pfppfp".
 */
typedef struct s_c_rule
{
	char	key;
	char	*rule;
}	t_c_rule;

/**
 * @brief propagate a seed to a certain depth.
 * @param lin the lindenmayer model to use.
 * @param seed the seed to propagate.
 * @param depth the depth to propagate.
 * 
 * Warning, the depth can be quite finiky and might need
 * tuning when propagating large rules/seeds.
 */
char	*prop(t_lin *lin, char *seed, int depth);

/**
 * @brief get the given char rule with a matching key.
 * @param rules the liked list of rules to lookup in.
 * @param key the character key to look for.
 */
t_c_rule	*rule_c_lookup(t_list *rules, char key);

/**
 * @brief add a new rule to the linked list of rules.
 * @param lin the lindenmayer model to add too.
 * @param key the character key to add.
 * @param rule the rule to add.
 * 
 * Note: Duplicate keys will be ignored instead of appended.
 */
void	append_c_rule(t_lin *lin, char key, char *rule);

/**
 * @brief transformation parameter
 * @param mag magnitude for linear movement.
 * @param euler angle for rotation.
 * @param data alternative data if required.
 */
union u_param
{
	int		mag;
	float	euler;
	void	*data;
};

/**
 * @brief Draw rule struct for use in linked list of draw rules.
 * @param key the character key for the rule.
 * @param f the function to call for the given char.
 * @param param data for use in f.
 */
typedef struct s_d_rule
{
	char	key;
	void	(*f)(t_lin *, union u_param);
	union u_param	param;
}	t_d_rule;

/**
 * @brief lookup a draw rule in the linked list of rules.
 * @param rules the linked list of rules.
 * @param key the ket to lookup.
 */
t_d_rule	*rule_d_lookup(t_list *rules, char key);

/**
 * @brief add a new rule to the list of draw rules.
 * @param lin the lindenmayer model to add the rule too.
 * @param key the key for the rule.
 * @param f the function to call for the key.
 * @param param the data to pass to f when called during drawing.
 * 
 * Note: unlike char rules appending a key that already exists will overwrite it.
 */
void	append_d_rule(t_lin *lin, char key,
			void (*f)(t_lin *, union u_param),
			union u_param param);

/**
 * Do draw will be replaced with something a bit better.
 */
void		do_draw(t_lin *master, char key);

// ███    ███  ██████  ██████  ███████ ██      
// ████  ████ ██    ██ ██   ██ ██      ██      
// ██ ████ ██ ██    ██ ██   ██ █████   ██      
// ██  ██  ██ ██    ██ ██   ██ ██      ██      
// ██      ██  ██████  ██████  ███████ ███████ 

/**
 * @brief cursor information
 * @param pos is the position of the cursor.
 * @param dir normal vector for the direction.
 * @param col colour (ignored!)
 */
typedef struct s_cur
{
	t_vec2		pos;
	t_vec2		dir;
	uint32_t	col;
}	t_cur;

/**
 * @brief The lindenmayer model.
 * 
 * Theres alot here, but the main things to note
 * are the rules and draw which are the linked lists for the
 * rules.
 * 
 * Scale and offset refer the the scale of the drawing
 * and the start position (cursor starts at 0,0 but offset
 * makes sure it starts a the center of the screen)
 * 
 * Canvas may be destoryed in order to re-draw, uncertain.
 */
typedef struct s_lin
{
	mlx_t		*mlx;
	mlx_image_t	*canvas;
	t_cur		*cursor;
	t_vec2		offset;
	double		scale;
	char		*seed;
	t_list		*rules;
	t_list		*draw;
	char		*model;
	double		delay;
	double		timer;
	int			dc;
	size_t		index;
	int			needs_redraw;
	void		*line;
	t_menu		*menu;
}	t_lin;

// ███    ███  █████  ████████ ██   ██ 
// ████  ████ ██   ██    ██    ██   ██ 
// ██ ████ ██ ███████    ██    ███████ 
// ██  ██  ██ ██   ██    ██    ██   ██ 
// ██      ██ ██   ██    ██    ██   ██ 

/**
 * @brief normalise a vector to it's magnitude
 * @param vec the vector.
 */
t_vec2	vec2_normalise(t_vec2 *vec);

/**
 * @brief returns the magnitude of a vector.
 * @param vec the vector to calc.
 */
double	vec2_magnitude(t_vec2 *vec);

/**
 * @brief add two vectors.
 * @param vec1 the first vector.
 * @param vec2 the second vector.
 */
t_vec2	vec2_add(t_vec2 *vec1, t_vec2 *vec2);

/**
 * @brief rotate a vector by a euler angle.
 * @param vec the normal vector to rotate.
 * @param angle the euler angle to rotate by.
 */
t_vec2	vec2_rotate_euler(t_vec2 *vec, float angle);

//  ██████  ████████ ██   ██ ███████ ██████  
// ██    ██    ██    ██   ██ ██      ██   ██ 
// ██    ██    ██    ███████ █████   ██████  
// ██    ██    ██    ██   ██ ██      ██   ██ 
//  ██████     ██    ██   ██ ███████ ██   ██ 

void	lin_redraw(void *param);
void	lin_key_hook(mlx_key_data_t keydata, void* param);

// default rules:

void	default_draw(t_lin *master, union u_param param);
void	default_rotate(t_lin *master, union u_param param);

/**
 * @brief Line prototype colour definition.
 * @param STAT Static colour (uint32).
 * @param GRAD Gradient (uint32[2]).
 * @param FUNC Function (Idk what prototype)
 */
enum e_colour
{
	STAT, GRAD, FUNC
};

/**
 * @brief Colour definition
 * @param stat static colour (for STAT enum)
 * @param grad array of colours (for GRAD enum)
 * @param func function to be called (for FUNC)
 */
union u_colour
{
	uint32_t	stat;
	uint32_t	*grad;
	uint32_t	(*func)(t_lin *, t_vec2[3], void *);
};

/**
 * @brief line prototype
 * @param thickness line thickness
 * @param c_type the type of colour
 * @param c_val the value of the colour
 * @param param the parameter to pass the func (if applicable)
 */
typedef struct s_line_proto
{
	float			thickness;
	enum e_colour	c_type;
	union u_colour	c_val;
	void			*param;
}	t_ln_proto;

/**
 * @brief Draws a line
 * @param start vec2 start of line
 * @param end vec2 end of line
 * @param model the lindenmayer model
 * @param proto line prototype
 */
void	draw_line(t_vec2 start,
			t_vec2 end, t_lin *model,
			t_ln_proto *proto);

// ██   ██  ██████   ██████  ██   ██ ███████ 
// ██   ██ ██    ██ ██    ██ ██  ██  ██      
// ███████ ██    ██ ██    ██ █████   ███████ 
// ██   ██ ██    ██ ██    ██ ██  ██       ██ 
// ██   ██  ██████   ██████  ██   ██ ███████ 

void	draw_hook(void *param);



#endif
