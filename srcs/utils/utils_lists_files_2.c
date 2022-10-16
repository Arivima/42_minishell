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

t_files	*remove_element_files(t_files *elem)
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

void	delete_list_files(t_files **list)
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
