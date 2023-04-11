/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:04 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 14:10:37 by hakahmed         ###   ########.fr       */
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
	if (!pid)
	{
		close(fd[WRITE_END]);
		int tfd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		char *line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (!ft_strncmp(dl, line, ft_strlen(line) - 1))
				break ;
			ft_putstr_fd(line, tfd);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
		// dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		exit(0);
	}
	else
	{
		// wait(NULL);
		waitpid(pid, &status, 0);
		// int fdo = open("out2", O_WRONLY);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		int tmpfd = open(".heredoc", O_RDONLY);
		dprintf(2,"%d\n", tmpfd);
		// (void) tmpfd;
		// dup(STDIN_FIL NO);
		dup2(tmpfd , STDIN_FILENO);
		int pid2 = ft_fork();
		if (!pid2)
		{
			ft_execute(cmd, envp);
		}
		// waitpid(pid2, NULL, 0);
		// unlink(".heredoc");
		// exit(0);
	}
}



// int main (int argc, char **argv, char  **envp)
// {
// 	(void) argc;
// 	ft_heredoc(argv[1], envp);
// }
