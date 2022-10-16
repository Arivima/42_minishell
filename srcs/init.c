/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:24:05 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:39:38 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	termcap_init(void)
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	if (term_type == NULL)
		return (ft_error_return("TERM must be set (see 'env').", -1));
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		return (ft_error_return("Can't access to the termcap database.", -1));
	return (0);
}

void	init_holder(t_hold *hold)
{
	hold->data = NULL;
	hold->param = NULL;
	hold->env = NULL;
	hold->env_arr = NULL;
	hold->std_in_out[0] = -1;
	hold->std_in_out[1] = -1;
	hold->line = NULL;
}

int	ft_set_loop(t_hold *hold, char **env)
{
	if (!hold->env)
	{
		hold->env = array_to_t_param(env);
		if (update_path_our_builtins(&hold->env) == -1)
			return (-1);
	}
	if (set_cpy_std_in_out(&hold->std_in_out[0], &hold->std_in_out[1]) == -1)
		return (-1);
	return (0);
}

int	ft_free_loop(t_hold *hold, char **line)
{
	if (hold->env_arr)
		ft_arr_free(hold->env_arr);
	if (hold->data)
		delete_list_data(&hold->data);
	if (*line)
		ft_free_reset_str(line);
	if (hold->line)
		ft_free_reset_str(&hold->line);
	if (close_cpy_std_in_out(hold->std_in_out) == -1)
		return (-1);
	return (0);
}
