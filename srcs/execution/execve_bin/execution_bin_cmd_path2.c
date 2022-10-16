/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bin_cmd_path2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:37:31 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/17 17:55:19 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_relative_path(char *relative_path)
{
	char	*pwd;
	char	*full_path;
	char	*tmp;

	if (!relative_path)
		return (ft_error_null("get_relative_path: no cmd", 0, ERR_DFLT));
	tmp = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_error_null("get_relative_path: PWD is NULL", 0, ERR_DFLT));
	if ((ft_strncmp(relative_path, "./", 2) == 0) && \
	(get_relative_path_single_dot(relative_path, &tmp) == -1))
		return (return_error_free(&pwd));
	else if ((ft_strncmp(relative_path, "../", 3) == 0) && \
	(get_relative_path_double_dot(relative_path, &tmp, &pwd) == -1))
		return (return_error_free(&pwd));
	else
		tmp = ft_strdup(relative_path);
	if (!tmp)
		return (return_error_free_msg(&pwd, "get_relative_path: ft_strdup"));
	full_path = ft_strjoin_three(pwd, "/", tmp);
	ft_free_reset_str(&pwd);
	ft_free_reset_str(&tmp);
	return (full_path);
}

int	get_relative_path_double_dot(char *rel_path, char **tmp, char **pwd)
{
	char	*tmp_pwd;
	int		n;

	tmp_pwd = NULL;
	n = 0;
	if (ft_strlen(rel_path) > 3)
	{
		*tmp = ft_substr(rel_path, 3, ft_strlen(rel_path));
		n = ft_strrchr_i(*pwd, '/');
		tmp_pwd = ft_substr(*pwd, 0, n);
		if (!tmp_pwd)
			return (ft_error("get_relative_path: ft_substr", 0, ERR_DFLT));
		free(*pwd);
		*pwd = ft_strdup(tmp_pwd);
		if (!pwd)
			return ((int) return_error_free_msg(&tmp_pwd, \
			"get_relative_path: ft_strdup"));
		ft_free_reset_str(&tmp_pwd);
	}
	else
		return (ft_error("../: is a directory", 0, 126));
	return (0);
}

int	get_relative_path_single_dot(char *relative_path, char **tmp)
{
	if (ft_strlen(relative_path) > 2)
	{
		*tmp = ft_substr(relative_path, 2, ft_strlen(relative_path));
		if (!*tmp)
			return (ft_error("get_relative_path_single_dot", 0, ERR_DFLT));
	}
	else
		return (ft_error("./: is a directory", 0, 126));
	return (0);
}

char	*return_error_free(char **str)
{
	ft_free_reset_str(str);
	return (NULL);
}

char	*return_error_free_msg(char **str, char *msg)
{
	ft_free_reset_str(str);
	return (ft_error_null(msg, 0, ERR_DFLT));
}
