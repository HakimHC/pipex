/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:35:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/12 16:43:24 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_redirect_in(char *cmd, char **envp, int fd[2], char *file)
{
	pid_t	pid;
	int		status;
	int	fdin;

	ft_pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		fdin = ft_open(file, O_RDONLY);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		dup2(fdin, STDIN_FILENO);
		close(fd[WRITE_END]);
		ft_execute(cmd, envp);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		waitpid(pid, &status, 0);
	}
}

int	no_bonus(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	fdin;
	int	fdout;
	int	pid;

	if (argc == 5)
	{
		ft_redirect_in(argv[2], envp, fd, argv[1]);
		fdout = ft_open(argv[4], O_CREAT | O_TRUNC | O_WRONLY);
		dup2(fdout, STDOUT_FILENO);
		ft_execute(argv[3], envp);
	}
	return (EXIT_FAILURE);
}

void	bonus_heredoc(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	i;
	int	fdout;

	ft_heredoc(argv[2], envp, argv[3], fd);
	i = 4;
	while (i < argc - 2)
		ft_redirect(argv[i++], envp, fd, 0);
	fdout = ft_open(argv[argc - 1], (O_CREAT | O_APPEND | O_WRONLY));
	dup2(fdout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
}

void	bonus_no_heredoc(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	fdin;
	int	fdout;
	int	i;

	ft_redirect_in(argv[2], envp, fd, argv[1]);
	i = 3;
	while (i < argc - 2)
		ft_redirect(argv[i++], envp, fd, 0);
	fdout = ft_open(argv[argc - 1], (O_CREAT | O_TRUNC | O_WRONLY));
	dup2(fdout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
}
