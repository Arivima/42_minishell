/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bin_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:48:02 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:39:29 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_bin_cmd(t_hold *hold, t_data *data)
{
	char	**full_path;

	if (update_cmd_our_builtins(&data->cmd_arg[0]) == -1)
		return (-1);
	hold->env_arr = param_to_array(&hold->env);
	full_path = get_execve_path(hold->env_arr, data->cmd_arg[0]);
	if (full_path && full_path[0] && full_path[0][0])
	{
		if (execute_execve(full_path, data->cmd_arg, hold->env_arr) == -1)
			ft_arr_free(full_path);
	}
	return (-1);
}

int	execute_execve(char **full_path, char **cmd_arg, char **env_arr)
{
	int	i;
	int	err;

	if (!cmd_arg || !*cmd_arg || !cmd_arg[0][0] \
	|| !env_arr || !*env_arr || !env_arr[0][0])
		return (ft_error("failure : empty cmd or env", "execve", ERR_DFLT));
	i = 0;
	while (full_path[i])
	{
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, SIG_DFL);
		if (execve(full_path[i], cmd_arg, env_arr) == -1)
		{
			err = errno;
			if (err == EACCES)
			{
				rl_clear_history();
				return (ft_error("Permission denied", cmd_arg[0], 126));
			}
		}
		i++;
	}
	rl_clear_history();
	return (ft_error("Command not found", cmd_arg[0], 127));
}

		/* FOR EVALUATION
		ft_putstr_fd("Testing order of directory check\n", 2);
		ft_putstr_fd(full_path[i], 2);
		ft_putstr_fd("\n", 2);
		*/
