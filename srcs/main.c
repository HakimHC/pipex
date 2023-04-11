/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:42:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/11 21:12:49 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	ft_abs_path(char *cmd)
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
	char	*cmd_exec;

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

void	exec_unlink(char *cmd, char **envp, int u)
{
	if (u)
	{
		if (!fork())
			ft_execute(cmd, envp);
		else
		{
			unlink(".heredoc");
			exit(0);
		}
	}
	ft_execute(cmd, envp);
}

void	ft_redirect(char *cmd, char **envp, int fd[2], int u)
{
	pid_t	pid;
	int		status;

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
		waitpid(pid, &status, 1);
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	printf("BONUS - %d\n", BONUS);
	if (BONUS == 0)
		return (no_bonus(argc, argv, envp));
	else if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
	{
		bonus_heredoc(argc, argv, envp);
		return (0);
	}
	else if (argc >= 5)
	{
		bonus_no_heredoc(argc, argv, envp);
		return (0);
	}
	return (EXIT_FAILURE);
}

////////////// TO DOOOOOOOOOO  ////////////////////
/// ---- HEREDOC O_APPEND ----- :D
/// ---- STRNCMP	------  :D
/// ---- ./ ../ etc
/// ---- FT_OPEN	------	:D
/// ---- ARGC		------  :D 
/// ---- MAKEFILE
/// ---- LIBFT CACHE A.OUT ETC	
