/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:23:31 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/02 18:23:33 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_file(t_data **head, int in_out, char *file, int type)
{
	t_data	*list_tmp;

	if (!*head)
	{
		*head = create_element_data();
		if (!(*head))
			return (-1);
	}
	list_tmp = *head;
	list_tmp = go_to_end_data(list_tmp);
	if (in_out == 0)
	{	
		append_element_file(&list_tmp->input, file, type);
		if (!list_tmp->input)
			return (-1);
	}
	else if (in_out == 1)
	{	
		append_element_file(&list_tmp->output, file, type);
		if (!list_tmp->output)
			return (-1);
	}
	else
		return (ft_error("append_file", 0, ERR_DFLT));
	return (0);
}

t_files	*create_element_files(char *file, int type)
{
	t_files	*elem;

	elem = malloc(sizeof(t_files));
	if (!elem)
		return ((t_files *) ft_error_null("create_element_files", \
		"malloc", ERR_DFLT));
	elem->file = ft_strdup(file);
	elem->type = type;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_files	*go_to_end_files(t_files *list)
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

t_files	*go_to_top_files(t_files *list)
{
	if (!list)
		return (NULL);
	while (list && list->prev)
		list = list->prev;
	return (list);
}

int	append_element_file(t_files **head, char *file, int type)
{
	t_files	*list_tmp;

	list_tmp = *head;
	if (!*head)
	{
		*head = create_element_files(file, type);
		if (!(*head))
			return (-1);
		else
			return (0);
	}
	list_tmp = go_to_end_files(list_tmp);
	list_tmp->next = create_element_files(file, type);
	list_tmp->next->prev = list_tmp;
	if (!list_tmp->next)
		return (-1);
	else
		return (0);
}
