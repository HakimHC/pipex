/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim </var/spool/mail/hakim>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:18:46 by hakim             #+#    #+#             */
/*   Updated: 2023/04/19 13:56:06 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirect_in(char *cmd, char **envp, int fd[2], char *file)
{
	pid_t	pid;
	int		fdin;

	ft_pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		fdin = ft_open(file, O_RDONLY);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		ft_execute(cmd, envp);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}
}

void	ft_redirect_out(char *file, int oflags, char **envp, char *cmd)
{
	int		fdout;
	int		status;
	pid_t	pid;

	fdout = ft_open(file, oflags);
	if (!ft_fork())
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		ft_execute(cmd, envp);
	}
	close(fdout);
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
	}
}

void	ft_redirect_pipe(char *cmd, char **envp, int fd[2], int u)
{
	pid_t	pid;

	ft_pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		exec_unlink(cmd, envp, u);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}
}
