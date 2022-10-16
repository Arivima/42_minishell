/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:23:53 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:38:30 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_reset_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_free_reset_arr(char ***arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (*arr[i])
	{
		free(*arr[i]);
		*arr[i] = NULL;
		i++;
	}
	if (*arr[i])
	{
		free(*arr[i]);
		*arr[i] = NULL;
	}
	free(*arr);
	*arr = NULL;
}
