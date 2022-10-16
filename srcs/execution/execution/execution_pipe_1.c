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

int	set_input(int *input)
{
	if (dup2(*input, STDIN_FILENO) < 0)
		return (ft_error("(input, STDIN_FILENO)", "dup2", ERR_DFLT));
	if (close(*input) < 0)
		return (ft_error("input", "close()", ERR_DFLT));
	*input = -1;
	return (0);
}

int	set_pipe(int pip[2])
{
	if (dup2(pip[1], STDOUT_FILENO) < 0)
		return (ft_error("pip[1], STDOUT_FILENO", "dup2", ERR_DFLT));
	if (close_pipe(&pip[0], &pip[1]) == -1)
		return (-1);
	return (0);
}

int	close_pipe(int *pip_0, int *pip_1)
{
	if (close(*pip_1) < 0)
		return (ft_error("pip[1]", "close()", ERR_DFLT));
	*pip_1 = -1;
	if (close(*pip_0) < 0)
		return (ft_error("pip[0]", "close()", ERR_DFLT));
	*pip_0 = -1;
	return (0);
}
