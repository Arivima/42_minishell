/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:18:51 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 18:18:52 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bin.h"

int	bin_ft_error_return(char *str, int ret)
{
	ft_putstr_fd(str, 2);
	return (ret);
}
