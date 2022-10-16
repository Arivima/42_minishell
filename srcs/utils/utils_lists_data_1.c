/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:23:19 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/02 18:23:22 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_element_data(t_data **head)
{
	t_data	*list_tmp;

	list_tmp = *head;
	if (!*head)
	{
		*head = create_element_data();
		if (!(*head))
			return (-1);
		else
			return (0);
	}
	list_tmp = go_to_end_data(list_tmp);
	list_tmp->next = create_element_data();
	if (!list_tmp->next)
		return (-1);
	list_tmp->next->prev = list_tmp;
	return (0);
}

t_data	*create_element_data(void)
{
	t_data	*elem;

	elem = malloc(sizeof(t_data));
	if (!elem)
		return ((t_data *) ft_error_null("create_element_data", \
		"malloc", ERR_DFLT));
	elem->cmd_arg = NULL;
	elem->input = NULL;
	elem->output = NULL;
	elem->fd[0] = -1;
	elem->fd[1] = -1;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_data	*go_to_end_data(t_data *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

t_data	*go_to_top_data(t_data *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

void	delete_list_data(t_data **list)
{
	t_data	*list_tmp;

	while (*list)
	{
		list_tmp = *list;
		*list = (*list)->next;
		if (list_tmp->cmd_arg && list_tmp->cmd_arg[0])
		{
			ft_arr_free(list_tmp->cmd_arg);
			list_tmp->cmd_arg = NULL;
		}
		if (list_tmp->input)
			delete_list_files(&list_tmp->input);
		if (list_tmp->output)
			delete_list_files(&list_tmp->output);
		list_tmp->prev = 0;
		list_tmp->next = 0;
		free(list_tmp);
	}
}
