/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:35:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 19:45:02 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	no_bonus(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	fdin;
	int	fdout;

	if (argc == 5)
	{
		ft_pipe(fd);
		fdin = ft_open(argv[1], O_RDONLY);
		dup2(fdin, STDIN_FILENO);
		ft_redirect(argv[2], envp, fd, 0);
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

	fdin = ft_open(argv[1], O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	i = 2;
	while (i < argc - 2)
		ft_redirect(argv[i++], envp, fd, 0);
	fdout = ft_open(argv[argc - 1], (O_CREAT | O_TRUNC | O_WRONLY));
	dup2(fdout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
}
