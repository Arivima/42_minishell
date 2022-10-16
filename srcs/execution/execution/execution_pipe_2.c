/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:47:50 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/05 16:47:52 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cpy_std_in_out(int *std_in, int *std_out)
{
	*std_in = dup(STDIN_FILENO);
	*std_out = dup(STDOUT_FILENO);
	if (*std_in < 0 || *std_out < 0)
		return (ft_error("dup(0) or dup(1)", 0, ERR_DFLT));
	return (0);
}

int	reset_std_in_out(int std_in_out[2])
{
	if (dup2(std_in_out[0], STDIN_FILENO) < 0)
		return (ft_error("dup2(std_in_out[0], 0)", 0, ERR_DFLT));
	if (dup2(std_in_out[1], STDOUT_FILENO) < 0)
		return (ft_error("dup2(std_in_out[1], 1)", 0, ERR_DFLT));
	return (0);
}

int	close_cpy_std_in_out(int std_in_out[2])
{
	if (std_in_out[1] >= 0)
	{
		if (close(std_in_out[1]) < 0)
			return (ft_error("close(std_in_out[1])", 0, ERR_DFLT));
		std_in_out[1] = -1;
	}
	if (std_in_out[0] >= 0)
	{
		if (close(std_in_out[0]) < 0)
			return (ft_error("close(std_in_out[0])", 0, ERR_DFLT));
		std_in_out[0] = -1;
	}
	return (0);
}
