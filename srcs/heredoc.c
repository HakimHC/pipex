/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:04 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 17:48:49 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	read_to_temp(char *dl)
{
	int		tfd;
	char	*line;

	tfd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(dl, line, ft_strlen(line) - 1))
			break ;
		write(tfd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(tfd);
}

void	ft_heredoc(char *dl, char **envp, char *cmd, int fd[2])
{
	int	tfd;

	read_to_temp(dl);
	tfd = open(".heredoc", O_RDONLY);
	dup2(tfd, STDIN_FILENO);
	ft_redirect(cmd, envp, fd, 1);
}
