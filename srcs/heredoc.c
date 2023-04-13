/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:04 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 01:45:54 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_to_temp(char *dl, char **envp)
{
	int		tfd;
	char	*line;

	dl = ft_strjoin(dl, "\n");
	tfd = ft_open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY);
	ft_printf("heredoc> ");
	wait(NULL);
	write(1, " ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strcmp(dl, line))
			break ;
		write(tfd, line, ft_strlen(line));
		free(line);
	ft_printf("heredoc> ");
	(void) envp;
	line = get_next_line(STDIN_FILENO);
	}
	free(dl);
	free(line);
	close(tfd);
}

void	ft_heredoc(char *dl, char **envp, char *cmd, int fd[2])
{
	int	tfd;

	if (!fork())
		ft_execute("bash tst.sh", envp);
	wait(NULL);
	read_to_temp(dl, envp);
	tfd = open(".heredoc", O_RDONLY);
	dup2(tfd, STDIN_FILENO);
	ft_redirect_pipe(cmd, envp, fd, 1);
}
