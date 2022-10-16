/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils_lists_data_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:32:11 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 18:37:59 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bin.h"

int	bin_ft_list_len_data(t_data *data)
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
