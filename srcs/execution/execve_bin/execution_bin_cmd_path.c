/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bin_cmd_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:36:48 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 20:33:26 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_execve_path(char **env_arr, char *cmd_arg)
{
	char	**full_path;

	full_path = NULL;
	if (cmd_arg[0] == '/' && ft_strlen(cmd_arg) > 1)
	{
		full_path = ft_arr_calloc(1, 0);
		free(full_path[0]);
		full_path[0] = ft_strdup(cmd_arg);
	}
	else if (cmd_arg[0] == '/' && ft_strlen(cmd_arg) == 1)
		return ((char **) ft_error_null("/: is a directory", 0, 126));
	else if (ft_is_path(cmd_arg))
		full_path = get_execve_path_2(full_path, cmd_arg);
	else
	{
		full_path = build_full_path_list(env_arr, cmd_arg);
		if (!full_path[0])
			return ((char **) \
			ft_error_null("No such file or directory", cmd_arg, 127));
	}
	return (full_path);
}

char	**get_execve_path_2(char **full_path, char *cmd_arg)
{
	char	*tmp;

	tmp = get_relative_path(cmd_arg);
	if (!tmp)
		return (NULL);
	full_path = (char **) malloc(sizeof(char *) * 2);
	if (!full_path)
		return (NULL);
	full_path[0] = (char *) malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!full_path[0])
		return (NULL);
	full_path[0] = ft_strdup(tmp);
	full_path[1] = NULL;
	ft_free_reset_str(&tmp);
	return (full_path);
}

int	ft_is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**build_full_path_list(char **env_arr, char *cmd)
{
	char	*tmp;
	char	**path;
	int		i;

	if (!env_arr || !*env_arr || !env_arr[0][0] || !cmd)
		return (NULL);
	path = get_path_list(env_arr);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return ((char **) ft_error_null("build_full_path_list \
			: ft_strjoin : tmp", 0, ERR_DFLT));
		free(path[i]);
		path[i] = NULL;
		path[i] = ft_strjoin(tmp, cmd);
		if (!path[i])
			return ((char **) ft_error_null("build_full_path_list \
			: ft_strjoin : path[i]", 0, ERR_DFLT));
		ft_free_reset_str(&tmp);
		i++;
	}
	return (path);
}

char	**get_path_list(char **env)
{
	int		i;
	char	**path;

	if (!env || !*env || !env[0][0])
		return (NULL);
	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		path = ft_arr_calloc(0, 0);
	else
		path = ft_split(env[i] + 5, ':');
	return (path);
}
