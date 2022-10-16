/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:17:01 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 18:49:56 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

void	bin_cd_correct_path(t_param *env, char *pwd)
{
	bin_change_var_value(&env, "OLDPWD", pwd);
	bin_ft_free_reset_str(&pwd);
	pwd = getcwd(NULL, 0);
	bin_change_var_value(&env, "PWD", pwd);
	bin_ft_free_reset_str(&pwd);
}

void	bin_cd_wrong_path(char *path)
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

char	*bin_cd_tilde_path(char *path, t_param *env)
{
	t_param	*home;
	char	*substr;
	char	*new_path;

	home = bin_search_var_param(&env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	substr = ft_substr(path, 1, ft_strlen(path) - 1);
	bin_ft_free_reset_str(&path);
	new_path = ft_strjoin(home->value, substr);
	free(substr);
	return (new_path);
}

int	bin_cd_path(char *path, t_param *env)
{
	char		*pwd;
	char		*new_path;

	pwd = getcwd(NULL, 0);
	if (ft_super_strncmp(path, "~/", 2) == 0)
	{
		new_path = bin_cd_tilde_path(path, env);
		if (!new_path)
		{
			bin_ft_free_reset_str(&pwd);
			return (1);
		}
	}
	else
		new_path = ft_strdup(path);
	if (chdir(new_path) == -1)
	{
		bin_cd_wrong_path(new_path);
		bin_ft_free_reset_str(&new_path);
		bin_ft_free_reset_str(&pwd);
		return (1);
	}
	bin_cd_correct_path(env, pwd);
	bin_ft_free_reset_str(&new_path);
	return (0);
}
