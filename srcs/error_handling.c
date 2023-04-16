/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:15:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/04/16 18:10:01 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(char *error)
{
	perror(error);
	exit(errno);
}

void	print_127(char *cmd)
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
	int	r;

	cmd_flags = ft_split(cmd, 32);
	if (ft_abs_path(cmd_flags[0]))
		cmd_exec = cmd_flags[0];
	else
		cmd_exec = get_cmd(path_arr(envp), cmd_flags[0], 0);
	ft_free_strarr(cmd_flags);
	r = !(!cmd_exec);
	if (cmd_exec)
		free(cmd_exec);
	return (r);
}

int	cmds_exists(int argc, char **argv, char **envp)
{
	char	*cmdf;
	char	**cmdp;
	char	*cmd;

	cmdf = argv[argc - 2];
	cmdp = ft_split(cmdf, 32);
	cmd = cmdp[0];
	if ((!is_in_path(cmd, envp) && access(cmd, X_OK))
		|| (access(cmd, X_OK) && !is_in_path(cmd, envp)))
		return (ft_free_strarr(cmdp), 0);
	return (ft_free_strarr(cmdp), 1);
}
