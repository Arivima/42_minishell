/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:24:05 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 19:52:43 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_hold	hold;

	if (av)
		;
	init_holder(&hold);
	signal(SIGINT, sig_handler);
	if (termcap_init() == -1)
		return (-1);
	while (ac == 1)
	{
		if (minishell(&hold, env) == -1)
			ft_exit(&hold, "print_exit");
	}
	return (0);
}

int	minishell(t_hold *hold, char **env)
{
	int		ret;

	g_stat.heredoc = 0;
	signal(SIGQUIT, SIG_IGN);
	if (ft_set_loop(hold, env) == -1)
		return (-1);
	hold->line = readline(PROMPT);
	add_history(hold->line);
	g_stat.heredoc = 1;
	if (hold->line == NULL)
		ft_exit(hold, "print_exit");
	if (hold->line && *hold->line)
	{
		ret = tokenize(hold->line, &hold->data);
		if (ret >= 0)
			ret = expansion(&hold->data, hold->env, hold->param);
		if (ret >= 0)
			ret = ft_execute(hold->data, hold);
	}
	if (ft_free_loop(hold, &hold->line) == -1)
		return (-1);
	return (0);
}
