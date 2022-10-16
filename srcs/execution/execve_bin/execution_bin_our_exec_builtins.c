/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bin_our_exec_builtins.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:47:37 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/24 17:06:52 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_path_our_builtins(t_param **env)
{
	char	*pwd;
	char	*our_builtin_path;
	t_param	*path;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_error("update_path_our_builtins: PWD is NULL", 0, ERR_DFLT));
	our_builtin_path = ft_strjoin_three(pwd, "/", "bin");
	ft_free_reset_str(&pwd);
	path = search_var_param(env, "PATH");
	tmp = ft_strjoin_three(path->value, ":", our_builtin_path);
	free(path->value);
	ft_free_reset_str(&our_builtin_path);
	path->value = ft_strdup(tmp);
	ft_free_reset_str(&tmp);
	return (0);
}

int	update_cmd_our_builtins(char **cmd)
{
	char	*val;

	val = NULL;
	if (!ft_super_strncmp(*cmd, "cd", 2) || !ft_super_strncmp(*cmd, "CD", 2))
		val = ft_strdup("our_cd");
	else if (!ft_super_strncmp(*cmd, "echo", 4)
		|| !ft_super_strncmp(*cmd, "ECHO", 4))
		val = ft_strdup("our_echo");
	else if (!ft_super_strncmp(*cmd, "pwd", 3)
		|| !ft_super_strncmp(*cmd, "PWD", 3))
		val = ft_strdup("our_pwd");
	else if (!ft_super_strncmp(*cmd, "export", 6))
		val = ft_strdup("our_export");
	else if (!ft_super_strncmp(*cmd, "unset", 5))
		val = ft_strdup("our_unset");
	else if (!ft_super_strncmp(*cmd, "env", 3)
		|| !ft_super_strncmp(*cmd, "ENV", 3))
		val = ft_strdup("our_env");
	else if (!ft_super_strncmp(*cmd, "exit", 4))
		val = ft_strdup("our_exit");
	else
		return (0);
	if (expand_word_update_line(cmd, 0, *cmd, &val) == -1)
		return (ft_error("expand_word_update_line", 0, ERR_DFLT));
	return (0);
}
