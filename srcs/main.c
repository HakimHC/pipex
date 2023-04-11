/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:42:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 03:43:46 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_abs_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] != '.' && cmd[0] != '~' && cmd[0] != '/')
		return (0);
	if (!access(cmd, X_OK))
		return (1);
	return (0);
}

void	ft_execute(char *cmd, char **envp)
{
	char	**cmd_flags;
	char *cmd_exec;

	cmd_flags = ft_split(cmd, 32);
	if (ft_abs_path(cmd_flags[0]))
		cmd_exec = cmd_flags[0];
	else
		cmd_exec = get_cmd(path_arr(envp), cmd_flags[0]);
	if (!cmd_exec)
		return (ft_free_strarr(cmd_flags));
	execve(cmd_exec, cmd_flags, envp);
	ft_free_strarr(cmd_flags);
	exit(EXIT_FAILURE);
}

void	ft_redirect(char *cmd, char **envp, int fd[2])
{
	pid_t pid;
	int status;

	ft_pipe(fd);
	pid = ft_fork();
	if (!pid)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_execute(cmd, envp);
	}
	else 
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		waitpid(pid, &status, 1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	// int fdin = open(argv[1], O_RDONLY);
	int fd[2];
	// if (fdin < 0)
	// 	perror_exit(argv[1]);
	// dup2(fdin, STDIN_FILENO);
	ft_heredoc(argv[2], envp, argv[3], fd);
	int i = 4;
	while (i < argc - 2)
		ft_redirect(argv[i++], envp, fd);
	int fdout = open(argv[argc - 1], (O_CREAT | O_TRUNC | O_WRONLY),
			(S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH));
	if (fdout < 0)
		perror_exit(argv[argc - 1]);
	dup2(fdout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
	return (EXIT_SUCCESS);
}
