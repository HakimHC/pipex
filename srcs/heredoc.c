/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:04 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 04:03:01 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	ft_heredoc(char *dl, char **envp, char *cmd, int fd[2])
{
	ft_pipe(fd);
	int status;
	pid_t pid = ft_fork();
	if (pid)
	{
		// ft_printf("heredoc> ");
		int tmpfd = open("tmp", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU );
		// close(fd[WRITE_END]);
		char *line = get_next_line(0);
		while (line)
		{
			if (!ft_strncmp(dl, line, ft_strlen(dl) - 1))
				break ;
			ft_putstr_fd(line, fd[WRITE_END]);
			// free(line);
			line = get_next_line(0);
		}
		free(line);
		// dup2(fd[READ_END], STDIN_FILENO);
		close(tmpfd);
		tmpfd = open("tmp", O_RDONLY);
		close(tmpfd);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		waitpid(pid, &status, 0);
		// exit(0);
		// ft_execute("cat", envp);
	}
	else
	{
		// waitpid(pid, &status, 0);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		// int pid2 = ft_fork();
		// if (!pid2)
		// {
		// 	char **rm = ft_split("rm -f tmp", 32);
		// 	execve(rm[0], rm, envp);
		// }
		// waitpid(pid2, NULL, -1);
		int tmpfd = open("tmp", O_RDONLY);
		dup2(tmpfd, STDIN_FILENO);
		ft_execute(cmd, envp);
	}
}



// int main (int argc, char **argv, char  **envp)
// {
// 	(void) argc;
// 	ft_heredoc(argv[1], envp);
// }
