/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:35:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 03:51:20 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void print_127(char *cmd)
{
	ft_putstr_fd("command not found: ", 2);
	if (cmd)
		ft_putendl_fd(cmd, 2);
	else
		ft_putendl_fd("", 2);
}

int	is_in_path(char *cmd, char **envp)
{
	char	**cmd_flags;
	char	*cmd_exec;

	cmd_flags = ft_split(cmd, 32);
	if (ft_abs_path(cmd_flags[0]))
		cmd_exec = cmd_flags[0];
	else
		cmd_exec = get_cmd(path_arr(envp), cmd_flags[0]);
	free(cmd_flags);
	return (!(!cmd_exec));
}

int	cmds_exists(int argc, char **argv, int h, char **envp)
{
	int i = 2;
	int pbool = 1;
	// ft_printf("v%d\n", i);
	if (h)
		i++;
	while (i < argc - 1)
	{
		if (!is_in_path(argv[i], envp))
		{
			if (access(argv[i], F_OK))
			{
				print_127(argv[i]);
				pbool = 0;
			}
		}
		i++;
	}
	return (pbool);
}

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
		if (!cmds_exists(argc, argv, 0, envp))
			return (127);
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
	if (!cmds_exists(argc, argv, 0, envp))
		exit(127);
	exit(0);
}
