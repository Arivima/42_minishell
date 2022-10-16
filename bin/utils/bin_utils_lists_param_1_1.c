/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils_lists_param_1_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:32:26 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 18:32:27 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bin.h"

int	bin_append_element_param(t_param **head, char *var, char *value)
{
	t_param	*list_tmp;

	list_tmp = *head;
	if (!*head)
	{
		*head = bin_create_element_param(var, value);
		if (!(*head))
			return (-1);
		else
			return (0);
	}
	list_tmp = bin_go_to_end_param(list_tmp);
	list_tmp->next = bin_create_element_param(var, value);
	if (!list_tmp->next)
		return (-1);
	list_tmp->next->prev = list_tmp;
	return (0);
}

t_param	*bin_create_element_param(char *var, char *value)
{
	t_param	*elem;

	elem = malloc(sizeof(t_param));
	if (!elem)
		return (NULL);
	elem->var = ft_strdup(var);
	if (!value)
		elem->value = NULL;
	else
		elem->value = ft_strdup(value);
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_param	*bin_go_to_end_param(t_param *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

t_param	*bin_go_to_top_param(t_param *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

void	bin_delete_list_param(t_param **list)
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
