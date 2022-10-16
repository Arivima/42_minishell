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

int	ft_list_len_data(t_data *data)
{
	t_data	*elem;
	int		i;

	elem = data;
	i = 0;
	if (elem)
	{
		i++;
		if (elem->next)
		{
			while (elem->next)
			{
				i++;
				elem = elem->next;
			}
		}
		return (i);
	}
	return (0);
}
