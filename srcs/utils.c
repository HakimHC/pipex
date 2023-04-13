/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:43:19 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 21:21:04 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_exit("fork");
	return (pid);
}

void	ft_pipe(int fd[2])
{
	int	p;

	p = pipe(fd);
	if (p < 0)
		perror_exit("pipe");
}

int	ft_open(char *file, int oflags)
{
	int	fd;

	fd = open(file, oflags, 0644);
	if (fd < 0)
		perror_exit(file);
	return (fd);
}

void	ft_execute(char *cmd, char **envp)
{
	char	**cmd_flags;
	char	*cmd_exec;

	cmd_flags = ft_split(cmd, 32);
	if (ft_abs_path(cmd_flags[0]))
		cmd_exec = cmd_flags[0];
	else
		cmd_exec = get_cmd(path_arr(envp), cmd_flags[0], 1);
	if (!cmd_exec)
		return (ft_free_strarr(cmd_flags), exit(EXIT_FAILURE));
	if (execve(cmd_exec, cmd_flags, envp) == -1)
	{
		ft_free_strarr(cmd_flags);
		perror_exit(cmd);
	}
}

void	exec_unlink(char *cmd, char **envp, int u)
{
	if (u)
		unlink(".heredoc");
	ft_execute(cmd, envp);
}
