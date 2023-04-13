/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:42:22 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/13 04:29:28 by hakahmed         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	// printf("BONUS - %d\n", BONUS);
	if (BONUS == 0)
		return (no_bonus(argc, argv, envp));
	else if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
		bonus_heredoc(argc, argv, envp);
	else if (argc >= 5)
		bonus_no_heredoc(argc, argv, envp);
	int fd = open("rocio", O_RDWR);
	(void) fd;
	ft_printf("%d\n", errno);
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
///
/// ---- infile error --> no outfile ---- :DDDDDDDDD
/// ---- pipex.h
/// ---- command not found
/// ---- sleep 5
