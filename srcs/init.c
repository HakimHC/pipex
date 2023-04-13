/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:35:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 21:19:51 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	no_bonus(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	*infile;
	char	*outfile;
	int		oflags;

	infile = argv[1];
	outfile = argv[4];
	oflags = O_CREAT | O_TRUNC | O_WRONLY;
	if (argc == 5)
	{
		ft_redirect_in(argv[2], envp, fd, infile);
		ft_redirect_out(outfile, oflags, envp, argv[3]);
		if (!cmds_exists(argc, argv, envp))
			return (127);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	bonus_heredoc(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		i;
	char	*outfile;
	int		oflags;

	outfile = argv[argc - 1];
	oflags = O_CREAT | O_APPEND | O_WRONLY;
	ft_heredoc(argv[2], envp, argv[3], fd);
	i = 4;
	while (i < argc - 2)
		ft_redirect_pipe(argv[i++], envp, fd, 0);
	ft_redirect_out(outfile, oflags, envp, argv[argc - 2]);
	if (!cmds_exists(argc, argv, envp))
		return (127);
	return (0);
}

int	bonus_no_heredoc(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		i;
	char	*infile;
	char	*outfile;
	int		oflags;

	infile = argv[1];
	outfile = argv[argc - 1];
	oflags = O_CREAT | O_TRUNC | O_WRONLY;
	ft_redirect_in(argv[2], envp, fd, infile);
	i = 3;
	while (i < argc - 2)
		ft_redirect_pipe(argv[i++], envp, fd, 0);
	ft_redirect_out(outfile, oflags, envp, argv[argc - 2]);
	if (!cmds_exists(argc, argv, envp))
		return (127);
	return (0);
}
