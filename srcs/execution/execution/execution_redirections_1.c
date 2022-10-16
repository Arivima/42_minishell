/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:47:37 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 16:26:38 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_redirections(t_data *data)
{
	if (data->input && \
	manage_redirections_infiles(&data->input, &data->fd[0]) == -1)
		return (-1);
	if (data->output && \
	manage_redirections_outfiles(&data->output, &data->fd[1]) == -1)
		return (-1);
	if (set_fd(data) == -1)
		return (-1);
	if (close_fd(data) == -1)
		return (-1);
	return (0);
}

int	manage_redirections_infiles(t_files **head, int *fd)
{
	t_files	*file;
	char	*filename;

	file = *head;
	while (file)
	{
		if (file->type == HEREDOC)
			filename = ft_strdup("minishell_heredoc.tmp");
		else
			filename = ft_strdup(file->file);
		if (manage_redirections_infiles_check_permission(filename) == -1)
			return (-1);
		if (file->next)
			file = file->next;
		else
		{
			if (manage_redirections_infiles_open_file(fd, filename) == -1)
				return (-1);
			break ;
		}
		ft_free_reset_str(&filename);
	}
	ft_free_reset_str(&filename);
	return (0);
}		

int	manage_redirections_infiles_open_file(int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		ft_error("Permission denied", filename, ERR_DFLT);
		ft_free_reset_str(&filename);
		return (-1);
	}
	return (0);
}

int	manage_redirections_infiles_check_permission(char *filename)
{
	if (access(filename, F_OK) < 0)
	{
		ft_error("no such file or directory", filename, ERR_DFLT);
		ft_free_reset_str(&filename);
		return (-1);
	}
	else if (access(filename, R_OK) < 0)
	{
		ft_error("Permission denied", filename, ERR_DFLT);
		ft_free_reset_str(&filename);
		return (-1);
	}
	return (0);
}

int	manage_redirections_outfiles(t_files **head, int *fd)
{
	t_files	*file;

	file = *head;
	while (file)
	{
		if (file->next)
		{
			if (close(open(file->file, O_CREAT | O_TRUNC | O_RDWR, 0644)) < 0)
				return (ft_error("close(open(file))", file->file, ERR_DFLT));
			file = file->next;
		}
		else
		{
			if (file->type == REDIR_APPEND)
				*fd = open(file->file, O_CREAT | O_APPEND | O_RDWR, 0644);
			else
				*fd = open(file->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (*fd < 0)
				return (ft_error("Permission denied:", file->file, ERR_DFLT));
			break ;
		}
	}
	return (0);
}
