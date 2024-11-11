/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 18:26:53 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-07 18:26:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lindenmayer.h"

t_c_rule	*rule_c_lookup(t_list *rules, char key)
{
	if (!key || !rules)
		return ((void *)0);
	while (rules)
	{
		if (rules->content
			&& ((t_c_rule *)rules->content)->key == key)
			return (rules->content);
		rules = rules->next;
	}
	return ((void *)0);
}

void	append_c_rule(t_lin *lin, char key, char *rule)
{
	t_list		*item;
	t_c_rule	*output;

	if (rule_c_lookup(lin->rules, key))
		return ;
	output = zeroit(malloc(sizeof(t_c_rule)), sizeof(t_c_rule));
	if (!output)
		return ;
	*output = (t_c_rule){key, rule};
	item = ft_lstnew(output);
	ft_lstadd_back(&lin->rules, item);
}

t_d_rule	*rule_d_lookup(t_list *rules, char key)
{
	if (!key || !rules)
		return ((void *)0);
	while (rules)
	{
		if (rules->content
			&& ((t_d_rule *)rules->content)->key == key)
			return (rules->content);
		rules = rules->next;
	}
	return ((void *)0);
}

void	append_d_rule(t_lin *lin, char key,
			void (*f)(t_lin *, union u_param),
			union u_param param)
{
	t_list		*item;
	t_d_rule	*output;

	if (rule_d_lookup(lin->draw, key))
	{
		rule_d_lookup(lin->draw, key)->param = param;
		rule_d_lookup(lin->draw, key)->f = f;
		return ;
	}
	output = zeroit(malloc(sizeof(t_d_rule)), sizeof(t_d_rule));
	if (!output)
		return ;
	*output = (t_d_rule){.key = key,
		.param = param,
		.f = f};
	item = ft_lstnew(output);
	ft_lstadd_back(&lin->draw, item);
}

void	do_draw(t_lin *master, char key)
{
	t_d_rule *r;
	r = rule_d_lookup(master->draw, key);
	if (!r)
		return;
	r->f(master, r->param);
}
