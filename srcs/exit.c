/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:14:27 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 19:52:39 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_hold *hold, char *print)
{
	if (ft_strncmp(print, "print_exit", 10) == 0)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	if (hold->data)
		delete_list_data(&hold->data);
	if (hold->param)
		delete_list_param(&hold->param);
	if (hold->env)
		delete_list_param(&hold->env);
	if (hold->env_arr)
		ft_arr_free(hold->env_arr);
	if (hold->line)
		ft_free_reset_str(&hold->line);
	close_cpy_std_in_out(hold->std_in_out);
	exit(g_stat.exit_stat);
}
