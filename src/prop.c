/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 18:09:14 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-07 18:09:14 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"



char	*prop(t_lin *lin, char *seed, int depth)
{
	char		*output;
	char		*tmp;
	t_c_rule	*rule;
	
	if (!seed || *seed == '\0')
		return (0);
	if (!depth)
		return (ft_strdup(seed));
	rule = rule_c_lookup(lin->rules, *seed++);
	if (!rule)
		return (0);
	output = ft_strdup(rule->rule);
	while(*seed)
	{
		rule = rule_c_lookup(lin->rules, *seed);
		if (!rule)
			tmp = ft_substr(seed, 0, 1);
		else
			tmp = ft_strdup(rule->rule);
		output = fancy_str_join(output, tmp, 3);
		seed++;
	}
	tmp = prop(lin, output, depth - 1);
	free(output);
	return (tmp);
}
