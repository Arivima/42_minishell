/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:23:42 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/09 18:49:26 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_element_param(t_param **head, char *var, char *value)
{
	t_param	*list_tmp;

	list_tmp = *head;
	if (!*head)
	{
		*head = create_element_param(var, value);
		if (!(*head))
			return (-1);
		else
			return (0);
	}
	list_tmp = go_to_end_param(list_tmp);
	list_tmp->next = create_element_param(var, value);
	if (!list_tmp->next)
		return (-1);
	list_tmp->next->prev = list_tmp;
	return (0);
}

t_param	*create_element_param(char *var, char *value)
{
	t_param	*elem;

	elem = malloc(sizeof(t_param));
	if (!elem)
		return ((t_param *) ft_error_null("create_element_param", \
		"malloc", ERR_DFLT));
	elem->var = ft_strdup(var);
	if (!value)
		elem->value = NULL;
	else
		elem->value = ft_strdup(value);
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_param	*go_to_end_param(t_param *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

t_param	*go_to_top_param(t_param *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

void	delete_list_param(t_param **list)
{
	t_param	*list_tmp;

	while (*list)
	{
		list_tmp = *list;
		*list = (*list)->next;
		if (list_tmp->var)
			free(list_tmp->var);
		list_tmp->var = 0;
		if (list_tmp->value)
			free(list_tmp->value);
		list_tmp->value = 0;
		list_tmp->prev = 0;
		list_tmp->next = 0;
		free(list_tmp);
	}
}
