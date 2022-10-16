/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils_lists_files_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:32:20 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 18:32:21 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bin.h"

t_files	*bin_remove_element_files(t_files *elem)
{
	t_files	*hand;

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
	free(elem->file);
	free(elem);
	elem = NULL;
	return (hand);
}

void	bin_delete_list_files(t_files **list)
{
	t_files	*list_tmp;

	while (*list)
	{
		list_tmp = *list;
		*list = (*list)->next;
		if (list_tmp->file)
			free(list_tmp->file);
		list_tmp->file = 0;
		list_tmp->type = 0;
		list_tmp->prev = 0;
		list_tmp->next = 0;
		free(list_tmp);
	}
}
