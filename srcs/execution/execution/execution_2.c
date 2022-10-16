/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:48:16 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:00:22 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_cmd(t_hold *hold, t_data *tmp, pid_t	*pid_arr_i, int *i)
{
	int		pip[2];
	int		in;
	pid_t	pid;

	in = -1;
	while (tmp)
	{
		if (tmp->next && pipe(pip))
			return (ft_error("pipe failure", "pipe", ERR_DFLT));
		if (tmp->input)
			set_heredoc(hold, &tmp->input);
		pid = fork();
		if (pid == -1)
			return (ft_error("failure fork", "fork_process_execve", ERR_DFLT));
		else if (pid == CHILD && (exec_child(hold, tmp, pip, in) == -1))
			ft_exit(hold, "no_print");
		else
			*pid_arr_i = pid;
		if ((tmp->next || tmp->prev) && fd_cl(tmp, &in, pip[0], &pip[1]) == -1)
			return (-1);
		if (next_cmd(&tmp, i) == -1)
			break ;
	}
	return (0);
}

int	next_cmd(t_data **temp, int *i)
{
	if ((*temp)->next)
	{
		(*temp) = (*temp)->next;
		(*i)++;
	}
	else
		return (-1);
	return (0);
}

int	exec_child(t_hold *hold, t_data *temp, int pip[2], int input)
{			
	if (temp->next && set_pipe(pip) == -1)
		return (-1);
	if (temp->prev && set_input(&input) == -1)
		return (-1);
	if (set_redirections(temp) == -1)
		return (-1);
	if (temp->cmd_arg)
	{
		if (execute_bin_cmd(hold, temp) == -1)
			ft_exit(hold, "no_print");
	}
	ft_exit(hold, "no_print");
	return (0);
}

int	fd_cl(t_data *temp, int *input, int pip_0, int *pip_1)
{
	if (temp->prev)
	{
		if (close(*input) < 0)
			return (ft_error("input", "close()", ERR_DFLT));
		*input = -1;
	}
	*input = pip_0;
	if (temp->next)
	{
		if (close(*pip_1) < 0)
			return (ft_error("pip[1]", "close()", ERR_DFLT));
		*pip_1 = -1;
	}
	return (0);
}

void	multiple_cmd_wait(int i, pid_t	*pid_arr)
{
	int	status;
	int	j;
	int	nb_cmd;

	j = 0;
	nb_cmd = i;
	while (j <= nb_cmd)
	{
		waitpid(pid_arr[j], &status, WUNTRACED);
		if (WIFEXITED(status))
				g_stat.exit_stat = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_stat.exit_stat = WTERMSIG(status) + 128;
		j++;
		i--;
	}
}
