/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections_heredoc_1.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:47:37 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 17:14:20 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_heredoc(t_hold *hold, t_files **head)
{
	t_files	*file;

	file = *head;
	while (file)
	{
		if (file->type == HEREDOC)
		{
			if (child_heredoc(hold, &file->file) == -1)
				return (-1);
		}
		if (file->next)
			file = file->next;
		else
			break ;
	}
	return (0);
}

int	child_heredoc(t_hold *hold, char **filename)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_error("fork_process_execve : failure fork", 0, ERR_DFLT));
	if (pid == CHILD && open_prompt_exec_heredoc(hold, filename) == -1)
		exit (EXIT_FAILURE);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_stat.exit_stat = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_stat.exit_stat = WTERMSIG(status) + 128;
		g_stat.heredoc = 0;
	}
	return (0);
}

int	open_prompt_exec_heredoc(t_hold *hold, char **filename)
{
	int		fd;
	char	*line;
	int		flag;

	g_stat.heredoc = 2;
	signal(SIGQUIT, SIG_IGN);
	if (open_fd_heredoc(&fd) == -1)
		return (-1);
	line = NULL;
	flag = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (error_close_exit_heredoc(fd));
		if (line)
		{
			flag = flag_heredoc(flag, filename);
			if (flag == 0 && expand_str(&line, hold->env, hold->param) == -1)
				return (-1);
			if (stop_print_close_heredoc(filename, fd, &line) == -1)
				return (-1);
		}
	}
	return (0);
}

int	open_fd_heredoc(int *fd)
{
	*fd = open("minishell_heredoc.tmp", O_CREAT | O_TRUNC | O_APPEND | O_RDWR, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (*fd < 0)
		return (ft_error("failed to open:", 0, ERR_DFLT));
	return (0);
}

int	stop_print_close_heredoc(char **filename, int fd, char **line)
{
	int	len;

	len = ft_strlen(*filename);
	if ((int) ft_strlen(*line) == len && !ft_memcmp(*filename, *line, len))
	{
		ft_free_reset_str(line);
		if (close(fd) == -1)
			return (ft_error("close(HERE_DOC)", 0, ERR_DFLT));
		exit (EXIT_SUCCESS);
	}
	ft_putstr_fd(*line, fd);
	ft_putstr_fd("\n", fd);
	ft_free_reset_str(line);
	return (0);
}
