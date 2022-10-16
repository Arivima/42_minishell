/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils_lists_files_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:32:16 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 18:32:17 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bin.h"

int	bin_append_file(t_data **head, int in_out, char *file, int type)
{
	t_data	*list_tmp;

	if (!*head)
	{
		*head = bin_create_element_data();
		if (!(*head))
			return (-1);
	}
	list_tmp = *head;
	list_tmp = bin_go_to_end_data(list_tmp);
	if (in_out == 0)
	{	
		bin_append_element_file(&list_tmp->input, file, type);
		if (!list_tmp->input)
			return (-1);
	}
	else if (in_out == 1)
	{	
		bin_append_element_file(&list_tmp->output, file, type);
		if (!list_tmp->output)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

t_files	*bin_create_element_files(char *file, int type)
{
	t_files	*elem;

	elem = malloc(sizeof(t_files));
	if (!elem)
		return (NULL);
	elem->file = ft_strdup(file);
	elem->type = type;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_files	*bin_go_to_end_files(t_files *list)
{
	if (!list)
		return (NULL);
	if (list && list->next)
	{
		while (list->next)
		list = list->next;
	}
	return (list);
}

t_files	*bin_go_to_top_files(t_files *list)
{
	if (!list)
		return (NULL);
	while (list && list->prev)
		list = list->prev;
	return (list);
}

int	bin_append_element_file(t_files **head, char *file, int type)
{
	t_files	*list_tmp;

	list_tmp = *head;
	if (!*head)
	{
		*head = bin_create_element_files(file, type);
		if (!(*head))
			return (-1);
		else
			return (0);
	}
	list_tmp = bin_go_to_end_files(list_tmp);
	list_tmp->next = bin_create_element_files(file, type);
	list_tmp->next->prev = list_tmp;
	if (!list_tmp->next)
		return (-1);
	else
		return (0);
}
