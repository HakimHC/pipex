/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:04 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 04:30:03 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	ft_heredoc(char *dl, char **envp, char *cmd, int fd[2])
{
	ft_pipe(fd);
	int status;
	pid_t pid = ft_fork();
	if (pid)
	{
		char *line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (!ft_strncmp(dl, line, ft_strlen(line) - 1))
				break ;
			ft_putstr_fd(line, fd[WRITE_END]);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		waitpid(pid, &status, -1);
	}
	else
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		int tmpfd = open("tmp", O_RDONLY);
		dup2(tmpfd, STDIN_FILENO);
		ft_execute(cmd, envp);
		exit(0);
	}
}



// int main (int argc, char **argv, char  **envp)
// {
// 	(void) argc;
// 	ft_heredoc(argv[1], envp);
// }
