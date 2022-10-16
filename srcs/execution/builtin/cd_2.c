/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:03:01 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 18:50:33 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_correct_path(t_param *env, char *pwd)
{
	change_var_value(&env, "OLDPWD", pwd);
	ft_free_reset_str(&pwd);
	pwd = getcwd(NULL, 0);
	change_var_value(&env, "PWD", pwd);
	ft_free_reset_str(&pwd);
}

void	cd_wrong_path(char *path)
{
	struct stat	info_dir;

	ft_putstr_fd("minishell: cd: ", 2);
	if (stat(path, &info_dir) == -1)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

char	*cd_tilde_path(char *path, t_param *env)
{
	t_param	*home;
	char	*substr;
	char	*new_path;

	home = search_var_param(&env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	substr = ft_substr(path, 1, ft_strlen(path) - 1);
	ft_free_reset_str(&path);
	new_path = ft_strjoin(home->value, substr);
	free(substr);
	return (new_path);
}

int	cd_path(char *path, t_param *env)
{
	char		*pwd;
	char		*new_path;

	pwd = getcwd(NULL, 0);
	if (ft_strncmp(path, "~/", 2) == 0)
	{
		new_path = cd_tilde_path(path, env);
		if (!new_path)
		{
			ft_free_reset_str(&pwd);
			return (1);
		}
	}
	else
		new_path = ft_strdup(path);
	if (chdir(new_path) == -1)
	{
		cd_wrong_path(new_path);
		ft_free_reset_str(&new_path);
		ft_free_reset_str(&pwd);
		return (1);
	}
	cd_correct_path(env, pwd);
	ft_free_reset_str(&new_path);
	return (0);
}
