/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:35:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/12 18:28:55 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	no_bonus(int argc, char **argv, char **envp)
{
	int	fd[2];
	char	*infile;
	char	*outfile;
	int	oflags;

	infile = argv[1];
	outfile = argv[4];
	oflags = O_CREAT | O_TRUNC | O_WRONLY;
	if (argc == 5)
	{
		ft_redirect_in(argv[2], envp, fd, infile);
		ft_redirect_out(outfile, oflags, envp, argv[3]);
		return (EXIT_SUCCESS);
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
		ft_redirect_pipe(argv[i++], envp, fd, 0);
	fdout = ft_open(argv[argc - 1], (O_CREAT | O_APPEND | O_WRONLY));
	dup2(fdout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
}


void	bonus_no_heredoc(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	i;
	char	*infile;
	char	*outfile;
	int	oflags;

	infile = argv[1];
	outfile = argv[argc - 1];
	oflags = O_CREAT | O_TRUNC | O_WRONLY;
	ft_redirect_in(argv[2], envp, fd, infile);
	i = 3;
	while (i < argc - 2)
		ft_redirect_pipe(argv[i++], envp, fd, 0);
	ft_redirect_out(outfile, oflags, envp, argv[argc - 2]);
	exit(0);
}
