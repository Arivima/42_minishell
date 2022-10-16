/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:48:16 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:00:16 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute(t_data *data, t_hold *hold)
{
	t_data	*temp;
	pid_t	*pid_arr;
	int		i;	

	if (is_more_cat(hold))
		signal(SIGQUIT, sig_handler);
	temp = data;
	if ((temp && (!temp->next && !temp->prev)) && single_cmd(hold, temp) == -1)
		return (-1);
	pid_arr = ft_calloc(ft_list_len_data(data), sizeof(*pid_arr));
	if (!pid_arr)
		return (ft_error("malloc pid_arr", "ft_execute", ERR_DFLT));
	i = 0;
	if (temp->next && multiple_cmd(hold, temp, &pid_arr[i], &i) == -1)
		return (-1);
	if (temp->next || temp->prev)
		multiple_cmd_wait(i, pid_arr);
	reset_std_in_out(hold->std_in_out);
	free(pid_arr);
	return (0);
}

int	single_cmd(t_hold *hold, t_data *temp)
{
	pid_t	pid_2;
	int		status_2;

	if (temp->input && set_heredoc(hold, &temp->input) == -1)
		return (-1);
	if (set_redirections(temp) == -1)
		return (-1);
	pid_2 = 0;
	status_2 = 0;
	if (temp->cmd_arg && is_builtin(temp, hold) == -1)
	{
		pid_2 = fork();
		signal(SIGQUIT, sig_handler);
		if (pid_2 == -1)
			ft_error("failure fork", "fork_process_execve", ERR_DFLT);
		else if (pid_2 == CHILD && execute_bin_cmd(hold, temp) == -1)
			ft_exit(hold, "no_print");
		waitpid(pid_2, &status_2, WUNTRACED);
		if (WIFEXITED(status_2))
			g_stat.exit_stat = WEXITSTATUS(status_2);
		if (WIFSIGNALED(status_2))
			g_stat.exit_stat = WTERMSIG(status_2) + 128;
	}
	return (0);
}

int	is_builtin(t_data *data, t_hold *hold)
{
	char	**cmd;

	cmd = data->cmd_arg;
	if (ft_word_match(cmd[0], "cd") || ft_word_match(cmd[0], "CD"))
		ft_cd(cmd, hold->env);
	else if (ft_word_match(cmd[0], "echo") || ft_word_match(cmd[0], "ECHO"))
		ft_echo(cmd);
	else if (ft_word_match(cmd[0], "pwd") || ft_word_match(cmd[0], "PWD"))
		ft_pwd();
	else if (ft_word_match(cmd[0], "export"))
		ft_export(cmd, hold);
	else if (ft_word_match(cmd[0], "unset"))
		ft_unset(cmd, hold);
	else if (ft_word_match(cmd[0], "env") || ft_word_match(cmd[0], "ENV"))
		ft_env(cmd, hold->env);
	else if (ft_word_match(cmd[0], "exit"))
		ft_exit_cmd(cmd, hold);
	else
		return (-1);
	return (0);
}
