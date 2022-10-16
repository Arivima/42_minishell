/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:24:13 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:41:34 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *msg, char *cmd, int exit_status)
{
	ft_putstr_fd(SHELL": ", 2);
	ft_putstr_fd("error: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd("error", 2);
	ft_putstr_fd("\n", 2);
	g_stat.exit_stat = exit_status;
	return (-1);
}

char	*ft_error_null(char *msg, char *cmd, int exit_status)
{
	ft_error(msg, cmd, exit_status);
	return (NULL);
}

int	ft_error_return(char *str, int ret)
{
	ft_putstr_fd(SHELL": ", 2);
	ft_putstr_fd("error: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("error", 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}
