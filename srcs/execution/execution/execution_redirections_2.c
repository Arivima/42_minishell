/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:47:37 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/26 15:15:38 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd(t_data *data)
{
	if (data->fd[1] >= 0)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) < 0)
			return (ft_error("dup2(data->fd[1], 1)", 0, ERR_DFLT));
	}
	if (data->fd[0] >= 0)
	{
		if (dup2(data->fd[0], STDIN_FILENO) < 0)
			return (ft_error("dup2(data->fd[0], 0)", 0, ERR_DFLT));
	}
	return (0);
}

int	close_fd(t_data *data)
{
	if (data->fd[1] >= 0)
	{
		if (close(data->fd[1]) < 0)
			return (ft_error("close(data->fd[1])", 0, ERR_DFLT));
		data->fd[1] = -1;
	}
	if (data->fd[0] >= 0)
	{
		if (close(data->fd[0]) < 0)
			return (ft_error("close(data->fd[0])", 0, ERR_DFLT));
		data->fd[0] = -1;
	}
	return (0);
}
