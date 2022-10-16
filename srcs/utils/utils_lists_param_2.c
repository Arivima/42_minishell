/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists_param_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:39:54 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:50:57 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*remove_element_param(t_param *elem)
{
	t_param	*hand;

	if (!elem)
		return (NULL);
	hand = NULL;
	if (elem->prev)
		(elem->prev)->next = elem->next;
	if (elem->next)
	{
		(elem->next)->prev = elem->prev;
		hand = elem->next;
	}
	else if (elem->prev)
		hand = elem->prev;
	else
		hand = NULL;
	free(elem->var);
	free(elem->value);
	free(elem);
	elem = NULL;
	return (hand);
}

int	change_var_value(t_param **env, char *var, char *val)
{
	t_param	*tmp;

	if (!(*env) || !var)
		return (-1);
	tmp = *env;
	while (tmp)
	{
		if (ft_super_strncmp(tmp->var, var, ft_strlen(var)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(val);
			return (0);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			return (-1);
	}
	return (-1);
}

void	delete_solo_elem_param(t_param *param)
{
	if (param)
	{
		free(param->var);
		free(param->value);
		free(param);
	}
}
